#pragma once
#include "data_block.h"
#include "serialization/reflection.h"
#include <config/config.h>

template<typename T>
void read(const DataBlock &blk, ecs::vector<T> &t);

template<typename T>
std::enable_if_t<HasReflection<T>::value, void> read(const DataBlock &blk, T &value);


template<typename T>
std::enable_if_t<!HasReflection<T>::value, void> read(const DataBlock &blk, T &t)
{
  if constexpr (std::is_constructible_v<T, const DataBlock &>)
  {
    t = T(blk);
  }
}


template<typename T>
void read(const DataBlock &blk, ecs::vector<T> &t)
{
  t.clear();
  if constexpr (std::is_same_v<T, eastl::string>)
  {
    constexpr size_t needType = DataBlock::AllowedTypes::getIndexOfType<std::string>();
    for (size_t i = 0, n = blk.propertiesCount(); i < n; i++)
      if (blk.getProperty(i).type == needType)
        t.push_back(blk.get<std::string>(blk.getProperty(i)).c_str());
  }
  else if constexpr (DataBlock::AllowedTypes::hasType<T>())
  {
    constexpr size_t needType = DataBlock::AllowedTypes::getIndexOfType<T>();
    for (size_t i = 0, n = blk.propertiesCount(); i < n; i++)
      if (blk.getProperty(i).type == needType)
        t.push_back(blk.get<T>(blk.getProperty(i)));
  }
  else
  {
    constexpr const std::string_view &typeName = nameOf<T>::value;
    for (size_t i = 0, n = blk.blockCount(); i < n; i++)
      if (blk.getBlock(i)->type() == typeName)
      {
        T &arg = t.emplace_back();
        read(*blk.getBlock(i), arg);
      }
  }
}

template<typename T>
std::enable_if_t<HasReflection<T>::value, void> read(const DataBlock &blk, T &value)
{
  value.reflect([&](auto &arg, const char *name)
  { 
    using TT = std::remove_cvref_t<decltype(arg)>;
    if constexpr (std::is_same_v<TT, eastl::string>)
    {
      const auto *component = blk.get<std::string>(name);
      if (component)
        arg = component->c_str();
    }
    else if constexpr (DataBlock::AllowedTypes::hasType<TT>())
    {
      const auto *component = blk.get<TT>(name);
      if (component)
        arg = *component;
    }
    else
    {
      const DataBlock *nonTrivialComponent = blk.getBlock(name);
      if (nonTrivialComponent)
        read(*nonTrivialComponent, arg);
    }
  });
}


template<typename T>
void write(DataBlock &blk, const T &value)
{

}


