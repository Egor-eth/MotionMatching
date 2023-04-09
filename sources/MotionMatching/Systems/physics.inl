#pragma once
#pragma clang optimize off
#include <ecs.h>
#include <vector>
#include <type_registration.h>
#include <bullet/btBulletDynamicsCommon.h>
#include "common.h"
#include "Animation/animation_player.h"
#include "Animation/person_controller.h"
#include "serialization/reflection.h"
#include "Physics/collision/body_generator.h"
#include "Physics/physical_object.h"
#include "Physics/bulletutil.h"
#include "Physics/collision/ragdoll_provider.h"
#include <iostream>

ECS_REGISTER_TYPE(BodyGenerator, BodyGenerator)
ECS_REGISTER_TYPE(RagdollProvider, RagdollProvider)
ECS_REGISTER_TYPE(PhysicalObject, PhysicalObject)

EVENT(scene=game; after=init_animation_character) init_world(const ecs::OnSceneCreated &)
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
  RigidBody *body = collision.createBody(physics, transform.get_transform(), pointerHolder);
  physics.init(ecs::get_singleton<World>(), true, {{0, body}}, pointerHolder);
  debug_log("Initialized simple body");
}

EVENT(scene=game; after=init_world) init_ragdoll(const ecs::OnSceneCreated &,
                                                     AnimationPlayer &animationPlayer,
                                                     PhysicalObject &physics,
                                                     const RagdollProvider &collision,
                                                     const Transform &transform)
{
  std::vector<btTypedConstraint *> pointerHolder;
  std::unordered_map<int, RigidBody*> bodies;
  collision.create(physics, animationPlayer, transform, bodies, pointerHolder);
  physics.init(ecs::get_singleton<World>(), true, bodies, pointerHolder);

  std::cout << bodies.size() << std::endl;
  debug_log("Initialized ragdoll");
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

SYSTEM(stage=before_act;scene=game; after=physics_update) physics_forward_sync_rgdl(
        Transform &transform,
        PhysicalObject &physics,
        AnimationPlayer &animationPlayer)
{
  mat4x4 inv = glm::inverse(transform.get_transform());
  AnimationTree &tree = animationPlayer.tree;
  for(auto &p : physics.getBodies())
  {
    const RigidBody &body = *p.second;
    mat4x4 tr;
    body.getTransform().getOpenGLMatrix(glm::value_ptr(tr));
    if(p.first == 1) {
      transform.set_from_mat(tr);
    }
    tr = inv * tr;
    tree.transforms[p.first] = tr;
    //Transform trs(tr);
    //tree.nodes[p.first].translation = glm::translate(mat4x4(1.0f), trs.get_position());
    //tree.nodes[p.first].rotation = mat4(trs.get_rotation());
  }
  //tree.calculate_bone_transforms();
}

SYSTEM(stage=before_act;scene=game; after=physics_update;require_not=AnimationPlayer animationPlayer) physics_forward_sync(
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

SYSTEM(stage=before_render; scene=game; require=PersonController personController) physics_backward_sync(
        Transform &transform,
        PhysicalObject &physics)
{
  physics.setFromGlTransform(transform);
}
