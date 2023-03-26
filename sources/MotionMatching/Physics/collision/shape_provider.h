#ifndef MOTIONMATCHING_SHAPE_PROVIDER_H
#define MOTIONMATCHING_SHAPE_PROVIDER_H
#include <btBulletDynamicsCommon.h>
#include <unordered_map>
#include <memory>
#include <ecs.h>

template<>
struct std::hash<btVector3>
{
  size_t operator()(const btVector3& vec) const
  {
    auto fhash = std::hash<float>{};
    return fhash(vec.getX()) + 31 * (fhash(vec.getY()) + 31 * fhash(vec.getZ()));
  }
};

template<>
struct std::hash<std::pair<btVector3, btCollisionShape*>>
{
  size_t operator()(const std::pair<btVector3, btCollisionShape*>& p) const
  {
    return std::hash<btVector3>{}(p.first) + 31 * std::hash<btCollisionShape*>{}(p.second);
  }
};


class ShapePool : ecs::Singleton {
public:
  ShapePool();
  btCollisionShape *getBoxShape(const btVector3 &size, const btVector3 &scale = {1, 1, 1});
  btCollisionShape *shiftedShape(btCollisionShape *shape, const btVector3 &shift);
  ShapePool &operator=(const ShapePool &) = delete;
  ShapePool(const ShapePool &) = delete;
private:
  std::unordered_map<std::pair<btVector3, btCollisionShape*>, std::unique_ptr<btCompoundShape>> compoundsByShift;
  std::unordered_map<btVector3, std::unique_ptr<btCollisionShape>> boxesBySize;
};

#endif
