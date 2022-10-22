#include "physics.inl"
#include <ecs_perform.h>
//Code-generator production

void update_func();

ecs::SystemDescription update_descr("update", {
  {ecs::get_type_description<BulletData>("bulletData"), false}
}, {
}, {},
{"motion_matching_update"},
{},
update_func, "act", {"game"}, false);

void update_func()
{
  ecs::perform_system(update_descr, update);
}

void init_world_handler(const ecs::Event &event);
void init_world_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription init_world_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneCreated>(), "init_world", {
  {ecs::get_type_description<BulletData>("bulletData"), false}
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

void create_bullet_handler(const ecs::Event &event);
void create_bullet_singl_handler(const ecs::Event &event, ecs::EntityId eid);

ecs::EventDescription create_bullet_descr(
  ecs::get_mutable_event_handlers<ecs::OnSceneDestroy>(), "create_bullet", {
  {ecs::get_type_description<BulletData>("bulletData"), false}
}, {
}, {},
{},
{},
create_bullet_handler, create_bullet_singl_handler, {});

void create_bullet_handler(const ecs::Event &event)
{
  ecs::perform_event((const ecs::OnSceneDestroy&)event, create_bullet_descr, create_bullet);
}
void create_bullet_singl_handler(const ecs::Event &event, ecs::EntityId eid)
{
  ecs::perform_event((const ecs::OnSceneDestroy&)event, create_bullet_descr, eid, create_bullet);
}


