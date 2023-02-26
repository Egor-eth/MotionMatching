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
#include <iostream>

//ECS_REGISTER_TYPE(World, World)
ECS_REGISTER_TYPE(BoxShape, BoxShape, true, true, true, true)
ECS_REGISTER_TYPE(RagdollChar, RagdollChar)
ECS_REGISTER_TYPE(PhysicalObject, PhysicalObject)

EVENT(scene=game) init_world(const ecs::OnSceneCreated &)
{
  World &world = ecs::get_singleton<World>();
  world->setGravity(btVector3(0, -10, 0));
  debug_log("World created");
}


EVENT(scene=game; after=init_world) init_static_box(const ecs::OnSceneCreated &,
                                  PhysicalObject &physics,
                                  const BoxShape &collision,
                                  const Transform *transform)
{
  physics.init(ecs::get_singleton<World>(), transform == nullptr ? Transform() : *transform, collision);
 // physics.getRoot()->applyCentralForce(btVector3(0, -10, 0));
  debug_log("Added BoxShape collision body");
}

EVENT(scene=game; after=init_world) init_ragdoll(const ecs::OnSceneCreated &,
                                  PhysicalObject &physics,
                                  const RagdollChar &collision,
                                  const Transform *transform)
{
  physics.init(ecs::get_singleton<World>(), transform == nullptr ? Transform() : *transform, collision);
}

SYSTEM(stage=before_act; scene=game) physics_update()
{
  //usleep(50);
  World &world = ecs::get_singleton<World>();
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
    vec3 pos = bt2glm(tr.getOrigin());
    std::cout.precision(3);
    transform.set_rotation(getRotation(tr));
  }
}

SYSTEM(stage=before_render; scene=game) physics_backward_sync(
        Transform &transform,
        PhysicalObject &physics)
{
  if(!physics.isStaticObject()) {
    physics.setFromGlTransform(transform);
    if(physics.getRoot()->getLinearVelocity().isZero()) {
      vec3 pos = bt2glm(getTransform(physics.getRoot()).getOrigin());
      std::cout.precision(4);
      std::cout << "btpos_bwd = " << pos.x << " " << pos.y << " " << pos.z << std::endl;
      pos = transform.get_position();
      std::cout << "glpos_bwd = " << pos.x << " " << pos.y << " " << pos.z << std::endl;
    }
  }
}
