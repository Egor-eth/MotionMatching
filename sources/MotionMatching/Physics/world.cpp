#include "world.h"

World::World() :
        collisionConfig(new btDefaultCollisionConfiguration()),
        dispatcher(new btCollisionDispatcher(collisionConfig)),
        overlappingPairCache(new btDbvtBroadphase()),
        constsicSolver(new btSequentialImpulseConstraintSolver),
        world(new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache,
                                          constsicSolver, collisionConfig))
{

}

World::~World()
{
  delete world;
  delete constsicSolver;
  delete overlappingPairCache;
  delete dispatcher;
  delete collisionConfig;
}