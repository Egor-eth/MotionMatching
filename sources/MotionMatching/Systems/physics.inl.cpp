#include "physics.inl"
#include <ecs_perform.h>
//Code-generator production

void physics_update_func();

ecs::SystemDescription physics_update_descr("physics_update", {
}, {
}, {"game"},
{},
{},
physics_update_func, "before_act", {}, false);

void physics_update_func()
{
  ecs::perform_system(physics_update_descr, physics_update);
}

void physics_forward_sync_func();

ecs::SystemDescription physics_forward_sync_descr("physics_forward_sync", {
  {ecs::get_type_description<Transform>("transform"), false},
  {ecs::get_type_description<PhysicalObject>("physics"), false}
}, {
}, {"game"},
{},
{"physics_update"},
physics_forward_sync_func, "before_act", {}, false);

void physics_forward_sync_func()
{
  ecs::perform_system(physics_forward_sync_descr, physics_forward_sync);
}

void physics_backward_sync_func();

ecs::SystemDescription physics_backward_sync_descr("physics_backward_sync", {
  {ecs::get_type_description<Transform>("transform"), false},
  {ecs::get_type_description<PhysicalObject>("physics"), false},
  {ecs::get_type_description<AnimationPlayer>("animationPlayer"), false}
}, {
}, {"game"},
{},
{},
physics_backward_sync_func, "before_render", {}, false);

void physics_backward_sync_func()
{
  ecs::perform_system(physics_backward_sync_descr, physics_backward_sync);
}

void init_world_handler(const ecs::Event &event);
void init_world_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_world_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_world", {
}, {
}, {"game"},
{},
{},
init_world_handler, init_world_singl_handler, {});

void init_world_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_world_descr, init_world);
}
void init_world_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_world_descr, eid, init_world);
}

void init_simple_body_handler(const ecs::Event &event);
void init_simple_body_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_simple_body_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_simple_body", {
  {ecs::get_type_description<PhysicalObject>("physics"), false},
  {ecs::get_type_description<BodyGenerator>("collision"), false},
  {ecs::get_type_description<Transform>("transform"), false}
}, {
}, {"game"},
{},
{"init_world"},
init_simple_body_handler, init_simple_body_singl_handler, {});

void init_simple_body_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_simple_body_descr, init_simple_body);
}
void init_simple_body_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_simple_body_descr, eid, init_simple_body);
}


