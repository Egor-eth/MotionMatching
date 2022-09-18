#include "render.inl"
#include <ecs_perform.h>
//Code-generator production

void add_global_uniform_handler(const ecs::Event &event);
void add_global_uniform_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription add_global_uniform_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "add_global_uniform", {
}, {
}, {},
{},
{},
add_global_uniform_handler, add_global_uniform_singl_handler, {});

void add_global_uniform_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, add_global_uniform_descr, add_global_uniform);
}
void add_global_uniform_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneCreated&)event, add_global_uniform_descr, eid, add_global_uniform);
}


