#include "shape_provider.h"
#include "Physics/bulletutil.h"

ShapePool::ShapePool()
{

}

btCollisionShape *ShapePool::getBoxShape(const btVector3 &size, const btVector3 &scale)
{
  btVector3 size_full = size * scale / 2.0f;
  return boxesBySize.try_emplace(size_full, new btBoxShape(size_full)).first->second.get();
}

btCollisionShape *ShapePool::shiftedShape(btCollisionShape* shape, const btVector3 &shift)
{
  auto p = std::pair(shift, shape);
  if(compoundsByShift.contains(p)) return compoundsByShift[p].get();

  btCompoundShape *compound = new btCompoundShape();
  btTransform tr = createIdentity();
  tr.setOrigin(shift);
  compound->addChildShape(tr, shape);
  compoundsByShift.insert({p, std::unique_ptr<btCompoundShape>(compound)});
  return compound;
}