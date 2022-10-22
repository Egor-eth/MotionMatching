#include <ecs.h>
#include <type_registration.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "common.h"

struct BulletData {
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *sicSolver;
  btDefaultCollisionConfiguration *collisionConfig;
  btDiscreteDynamicsWorld *world;
};
ECS_REGISTER_TYPE(BulletData, BulletData)

EVENT(scene=game) init_world(const ecs::OnSceneCreated &, BulletData &bulletData)
{
  bulletData.collisionConfig = new btDefaultCollisionConfiguration();
  bulletData.dispatcher = new btCollisionDispatcher(bulletData.collisionConfig);
  bulletData.overlappingPairCache = new btDbvtBroadphase();
  bulletData.sicSolver = new btSequentialImpulseConstraintSolver;
  bulletData.world = new btDiscreteDynamicsWorld(bulletData.dispatcher, bulletData.overlappingPairCache,
                                                 bulletData.sicSolver, bulletData.collisionConfig);

  bulletData.world->setGravity(btVector3(0, -10, 0));
}

EVENT() create_bullet(const ecs::OnSceneDestroy &, BulletData &bulletData)
{
  delete bulletData.world;
  delete bulletData.sicSolver;
  delete bulletData.overlappingPairCache;
  delete bulletData.dispatcher;
  delete bulletData.collisionConfig;
}

SYSTEM(stage=act;before=motion_matching_update; tags=game) update(
        BulletData bulletData)
{
  bulletData.world->stepSimulation(1.0f/60.0f, 10);
}