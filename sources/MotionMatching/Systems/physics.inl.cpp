#include "physics.inl"
#include <ecs_perform.h>
//Code-generator production

void physics_update_func();

ecs::SystemDescription physics_update_descr("physics_update", {
  {ecs::get_type_description<World>("world"), false}
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
  {ecs::get_type_description<PhysicalObject>("physics"), false}
}, {
}, {"game"},
{},
{},
physics_backward_sync_func, "before_render", {}, false);

void physics_backward_sync_func()
{
  ecs::perform_system(physics_backward_sync_descr, physics_backward_sync);
}

void init_static_box_handler(const ecs::Event &event);
void init_static_box_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_static_box_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_static_box", {
  {ecs::get_type_description<PhysicalObject>("physics"), false},
  {ecs::get_type_description<BoxShape>("collision"), false},
  {ecs::get_type_description<Transform>("transform"), true},
  {ecs::get_type_description<World>("world"), false}
}, {
}, {"game"},
{},
{},
init_static_box_handler, init_static_box_singl_handler, {});

void init_static_box_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_static_box_descr, init_static_box);
}
void init_static_box_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_static_box_descr, eid, init_static_box);
}

void init_ragdoll_handler(const ecs::Event &event);
void init_ragdoll_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_ragdoll_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_ragdoll", {
  {ecs::get_type_description<PhysicalObject>("physics"), false},
  {ecs::get_type_description<RagdollChar>("collision"), false},
  {ecs::get_type_description<Transform>("transform"), true},
  {ecs::get_type_description<World>("world"), false}
}, {
}, {"game"},
{},
{},
init_ragdoll_handler, init_ragdoll_singl_handler, {});

void init_ragdoll_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_ragdoll_descr, init_ragdoll);
}
void init_ragdoll_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, init_ragdoll_descr, eid, init_ragdoll);
}

void init_world_handler(const ecs::Event &event);
void init_world_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_world_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_world", {
  {ecs::get_type_description<World>("world"), false}
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


