#include "template.h"
#include "serialization/serialization.h"
#include "application/application_data.h"
#include "data_block/data_block.h"
#include "manager/entity_id.h"
#include <filesystem>
#include <map>
namespace fs = std::filesystem;
using namespace std;

namespace ecs
{ 
  struct TemplateFile
  {
    std::string path;
    DataBlockPtr fileBlk;
    TemplateFile(const std::string &path, DataBlockPtr fileBlk):
      path(path), fileBlk(fileBlk)
    {}
  };
  
  struct RawTemplate
  {
    std::string name;
    const DataBlock* blk;
    vector<ComponentInstance> components;
    vector<std::string> extends;
    vector<size_t> extendsIdx;
  };
  template<typename T>
  ComponentInstance create_instance(const DataBlock &blk, const DataBlock::Property &property)
  {
    return ComponentInstance(property.name.c_str(), blk.get<T>(property));
  }
  template<>
  ComponentInstance create_instance<std::string>(const DataBlock &blk, const DataBlock::Property &property)
  {
    return ComponentInstance(property.name.c_str(), ecs::string(blk.get<std::string>(property).c_str()));
  }
  GET_FUNCTIONS(instantiate, create_instance)


  static void collect_template_files(vector<TemplateFile> &templatesFiles)
  {
    templatesFiles.clear();
    for (const auto &path : Application::instance().templatePaths)
    {
      if (!fs::exists(path))
        continue;
      for (const auto & entry : fs::recursive_directory_iterator(path))
      {
        if (entry.is_regular_file() && entry.path().extension() == ".blk")
        {
          std::string strPath = entry.path().string();
          templatesFiles.emplace_back(strPath, make_shared<DataBlock>(strPath));
        }
      }
    }
  }

  static void fill_raw_template(const vector<TemplateFile> &templateFiles, vector<RawTemplate> &rawTemplates)
  {
    for (const TemplateFile &file : templateFiles)
    {
      const DataBlock &blk = *file.fileBlk.get();
      for (size_t tmplId = 0, tmplN = blk.blockCount(); tmplId < tmplN; tmplId++)
      {
        const DataBlock *tmpl = blk.getBlock(tmplId);
        assert(tmpl);
        RawTemplate &rawTemplate = rawTemplates.emplace_back();
        rawTemplate.name = tmpl->name();
        rawTemplate.blk = tmpl;
        for (size_t i = 0, n = tmpl->propertiesCount(); i < n; i++)
        {
          const DataBlock::Property &property = tmpl->getProperty(i);
          if (property.name == "_extends")
            rawTemplate.extends.emplace_back(tmpl->get<std::string>(property));
        }
      }
    }
  }

  enum {
    NOT_VISITED,
    VISITED,
    VERIFIED,
    NOT_VERIFIED
  };

  static bool validate_template(const vector<RawTemplate> &templates, size_t templateId, vector<int> &status)
  {
    if (status[templateId] == VERIFIED)
      return true;
    if (status[templateId] == NOT_VERIFIED || status[templateId] == VISITED)
      return false;
      
    status[templateId] = VISITED;
    for (const std::string &extends : templates[templateId].extends)
    {
      bool hasExtends = false;
      for (size_t i = 0, n = templates.size(); i < n; ++i)
        if (templates[i].name == extends)
        {
          if (!validate_template(templates, i, status))
            return false;
          hasExtends = true;
        }
      if (!hasExtends)
        debug_error("don't exists extends \"%s\" for template \"%s\"", extends.c_str(), templates[templateId].name.c_str());
    }
    status[templateId] = VERIFIED;
    return true;
  }

  static void validate_templates(vector<RawTemplate> &templates)
  {
    vector<int> status(templates.size(), NOT_VISITED);
    for (size_t i = 0, n = templates.size(); i < n; ++i)
    {
      if (!validate_template(templates, i, status))
      {
        debug_error("template \"%s\" has cyclic dependencies!", templates[i].name.c_str());
      }
    }
    size_t first = 0, last = templates.size();
    for(; first < last; ++first)
      if (status[first] != VERIFIED)
        break;
    if (first != last)
      for(size_t i = first, n = templates.size(); ++i < n;)
        if (status[i] != VERIFIED)
        {
          templates[first] = std::move(templates[i]);
          first++;
        }
    templates.erase(templates.begin() + first, templates.end());
  }

  static void init_templates(vector<RawTemplate> &rawTemplates)
  {
    for (RawTemplate &rawTmpl : rawTemplates)
    {
      for (const std::string &extends : rawTmpl.extends)
      {
        auto it = find_if(rawTemplates.begin(), rawTemplates.end(), [&](const RawTemplate&tmpl) {return tmpl.name == extends;});
        if (it != rawTemplates.end())
          rawTmpl.extendsIdx.emplace_back(it - rawTemplates.begin());
        else
          debug_error("undefined extend %s in %s", extends.c_str(), rawTmpl.name.c_str());
      }
    }
  }

  void init_components_from_blk(const DataBlock *tmpl, vector<ComponentInstance> &components)
  {
    const auto &typeMap = ecs::TypeInfo::types();
    for (size_t i = 0, n = tmpl->propertiesCount(); i < n; i++)
    {
      const DataBlock::Property &property = tmpl->getProperty(i);
      if (property.name != "_extends" && property.name != "_template")
      {
        components.emplace_back(instantiate[property.type](*tmpl, property));
      }
    }
    for (size_t i = 0, n = tmpl->blockCount(); i < n; i++)
    {
      const DataBlock *property = tmpl->getBlock(i);
  
      auto it = typeMap.find(HashedString(property->type().c_str()));
      if (it != typeMap.end())
      {
        const ecs::TypeInfo &typeInfo = *it->second;
        components.emplace_back(typeInfo, property->name().c_str(),
          [property, reader = typeInfo.userInfo.blkReader](void *raw_data) {
          reader(*property, raw_data);
        });
       ;
      }
      else
      {
        debug_error("unknown type %s:%s", property->name().c_str(),  property->type().c_str());
      }
    }
  }

  static void init_components(const RawTemplate &rawTemplate, vector<ComponentInstance> &components)
  {
    init_components_from_blk(rawTemplate.blk, components);
    components.emplace_back(ComponentInstance("eid", ecs::EntityId()));
  }



  static void linearize_extends(vector<RawTemplate> &rawTemplates, size_t templateId)
  {
    RawTemplate &blkTemplate = rawTemplates[templateId];
    if (!blkTemplate.components.empty())
      return;
    
    for (size_t i : rawTemplates[templateId].extendsIdx)
    {
      linearize_extends(rawTemplates, i);
      patch_components(blkTemplate.components, rawTemplates[i].components);
    }
    vector<ComponentInstance> components;
    init_components(rawTemplates[templateId], components);
    patch_components(blkTemplate.components, std::move(components));

  }

  static void linearize_extends(vector<RawTemplate> &rawTemplates)
  {
    for (size_t i = 0, n = rawTemplates.size(); i < n; ++i)
    {
      linearize_extends(rawTemplates, i);
    }
  }

  void load_templates_from_blk()
  {
    static vector<TemplateFile> templatesFiles;
    templatesFiles.clear();
    collect_template_files(templatesFiles);

    vector<RawTemplate> rawTemplates;
    fill_raw_template(templatesFiles, rawTemplates);
  
    validate_templates(rawTemplates);//remove cyclic dependencies
  
    init_templates(rawTemplates);

    linearize_extends(rawTemplates);

    for (RawTemplate &tmpl : rawTemplates)
      ecs::create_template(tmpl.name.c_str(), std::move(tmpl.components));
  }
}