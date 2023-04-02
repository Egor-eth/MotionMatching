#pragma once
#pragma clang optimize off
#include <ecs.h>
#include <vector>
#include <type_registration.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "common.h"
#include "Animation/animation_player.h"
#include "serialization/reflection.h"
#include "Physics/collision/body_generator.h"
#include "Physics/physical_object.h"
#include "Physics/world.h"
#include "Physics/bulletutil.h"
#include "Physics/debug_drawer.h"
#include <iostream>

ECS_REGISTER_TYPE(BodyGenerator, BodyGenerator)
ECS_REGISTER_TYPE(PhysicalObject, PhysicalObject)

EVENT(scene=game) init_world(const ecs::OnSceneCreated &)
{
  World &world = ecs::get_singleton<World>();
  world->setGravity(btVector3(0, -10, 0));
  world.markInit();
  debug_log("World created");

}


EVENT(scene=game; after=init_world) init_simple_body(const ecs::OnSceneCreated &,
                                  PhysicalObject &physics,
                                  const BodyGenerator &collision,
                                  const Transform &transform)
{
  std::vector<btTypedConstraint *> pointerHolder;
  RigidBody * body = collision.createBody(physics, transform.get_transform(), pointerHolder);
  physics.init(ecs::get_singleton<World>(), true, {{0, body}}, pointerHolder);
  debug_log("Initialized simple body");
}

SYSTEM(stage=before_act; scene=game) physics_update()
{
  World &world = ecs::get_singleton<World>();
  if(!world.initialized()) {
    debug_log("Physics update called before world initialization");
  } else {
    float dt = Time::delta_time();
    world->stepSimulation(dt, 60);
  }
}

SYSTEM(stage=before_act;scene=game; after=physics_update) physics_forward_sync(
        Transform &transform,
        PhysicalObject &physics)
{

  if(!physics.getRoot()->isStaticObject()) {
    RigidBody &body = physics.getRoot();
    btTransform tr = body.getMotionStateTransform();

    transform.set_position(bt2glm(tr.getOrigin() + body.getShift()));
    transform.set_rotation(getRotation(tr));
  }
}

SYSTEM(stage=before_render; scene=game; require=AnimationPlayer animationPlayer) physics_backward_sync(
        Transform &transform,
        PhysicalObject &physics)
{
  physics.setFromGlTransform(transform);
}
