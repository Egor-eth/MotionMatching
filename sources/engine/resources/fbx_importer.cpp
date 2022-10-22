#include "fbx_importer.h"
#include "resource_registration.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "render/mesh.h"

void FBXMeta::create_assets() const
{

  for (const std::string &str : meshMetaData)
  { 
    Asset<Mesh> mesh(str);
  }
}

bool FBXMeta::after_construct(const std::filesystem::path &path)
{
  if (loaded)
  {
    create_assets();
    return false;
  }
  else
  {
    read_file_info(path);
    create_assets();
    loaded = true;
    return true;
  }
}

void FBXMeta::read_file_info(const std::filesystem::path &path)
{
  Assimp::Importer importer;
  importer.SetPropertyBool(AI_CONFIG_IMPORT_FBX_PRESERVE_PIVOTS, false);
  importer.SetPropertyFloat(AI_CONFIG_GLOBAL_SCALE_FACTOR_KEY, 1.f);
#ifdef __WIN32
  std::string fbxPath = path.parent_path().string() + "\\" + path.stem().string();
#else
  std::string fbxPath = path.parent_path().string() + "/" + path.stem().string();
#endif
  importer.ReadFile(fbxPath, aiPostProcessSteps::aiProcess_Triangulate | aiPostProcessSteps::aiProcess_LimitBoneWeights |
    aiPostProcessSteps::aiProcess_GenNormals | aiProcess_GlobalScale | aiProcess_FlipWindingOrder);

  const aiScene* scene = importer.GetScene();
  if (!scene)
  {
    debug_error("no asset in %s", fbxPath.c_str());
    return;
  }
  std::filesystem::path resourceRoot = root_path();
  for (uint i = 0; i < scene->mNumMeshes; ++i)
  {
    std::filesystem::path path_ = (fbxPath + "[" + std::to_string(i) + "]" );
    meshMetaData.emplace_back(path_.lexically_relative(resourceRoot).string());
    debug_log("find new mesh %s", meshMetaData.back().c_str());
  }
  importer.FreeScene();

}

void FBXMeta::load(const std::filesystem::path &path, bool reload, AssetStatus &status)
{
  if (reload || loaded)
    return;
  read_file_info(path);
  create_assets();
  loaded = true;
  status = AssetStatus::Loaded;
}
ResourceRegister<FBXMeta> fbxImrorter({".fbx", ".dae"});