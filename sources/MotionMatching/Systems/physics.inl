#pragma once
#include <ecs.h>
#include <vector>
#include <type_registration.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "common.h"
#include "serialization/reflection.h"
#include "Physics/collision/box_shape.h"
#include "Physics/collision/ragdoll_char.h"
#include "Physics/physical_object.h"
#include "Physics/world.h"
#include "Physics/bulletutil.h"

//ECS_REGISTER_TYPE(World, World)
ECS_REGISTER_TYPE(BoxShape, BoxShape, true, true, true, true)
ECS_REGISTER_TYPE(RagdollChar, RagdollChar)
ECS_REGISTER_TYPE(PhysicalObject, PhysicalObject)

EVENT(scene=game) init_static_box(const ecs::OnSceneCreated &,
                                  PhysicalObject &physics,
                                  const BoxShape &collision,
                                  const Transform *transform,
                                  World &world)
{
  physics.init(world, transform == nullptr ? Transform() : *transform, collision);
}

EVENT(scene=game) init_ragdoll(const ecs::OnSceneCreated &,
                                  PhysicalObject &physics,
                                  const RagdollChar &collision,
                                  const Transform *transform,
                                  World &world)
{
  physics.init(world, transform == nullptr ? Transform() : *transform, collision);
}

EVENT(scene=game) init_world(const ecs::OnSceneCreated &,
                             World &world)
{
  world->setGravity(btVector3(0, 0, 0));
}

SYSTEM(stage=before_act; scene=game) physics_update(
        World &world)
{
  //usleep(50);
  float dt = Time::delta_time();
  world->stepSimulation(dt, 10);
}

SYSTEM(stage=before_act;scene=game; after=physics_update) physics_forward_sync(
        Transform &transform,
        PhysicalObject &physics)
{
  if(!physics.isStaticObject()) {
    btRigidBody *body = physics.getRoot();
    btTransform tr = getTransform(body);

    transform.set_position(physics.getGlPosition());
    btQuaternion quat = tr.getRotation();
    transform.set_rotation(quat[0], quat[1], quat[2]);
  }
}

SYSTEM(stage=before_render; scene=game) physics_backward_sync(
        Transform &transform,
        PhysicalObject &physics)
{
  physics.setFromGlTransform(transform);
}
