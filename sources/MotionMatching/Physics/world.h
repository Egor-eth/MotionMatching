#pragma once
#include <ecs.h>
#include <bullet/btBulletDynamicsCommon.h>

class World : ecs::Singleton {
public:
  World();
  ~World();

  operator btDiscreteDynamicsWorld*()
  {
    return world;
  }

  btDiscreteDynamicsWorld *get_world()
  {
    return world;
  }

  btDiscreteDynamicsWorld* operator->()
  {
    return world;
  }

private:
  btDefaultCollisionConfiguration * const collisionConfig;
  btCollisionDispatcher * const dispatcher;
  btBroadphaseInterface * const overlappingPairCache;
  btSequentialImpulseConstraintSolver * const constsicSolver;
  btDiscreteDynamicsWorld *const world;
};