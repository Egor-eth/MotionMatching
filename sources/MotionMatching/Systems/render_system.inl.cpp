#include "render_system.inl"
#include <ecs_perform.h>
//Code-generator production

ecs::QueryDescription find_box_shapes_descr("find_box_shapes", {
  {ecs::get_type_description<PhysicalObject>("physics"), false}
}, {
});

template<typename Callable>
void find_box_shapes(Callable lambda)
{
  ecs::perform_query<PhysicalObject&>
  (find_box_shapes_descr, lambda);
}


void process_animation_func();

ecs::SystemDescription process_animation_descr("process_animation", {
  {ecs::get_type_description<Asset<Mesh>>("mesh"), false},
  {ecs::get_type_description<AnimationPlayer>("animationPlayer"), false},
  {ecs::get_type_description<Transform>("transform"), false},
  {ecs::get_type_description<Settings>("settings"), false}
}, {
}, {"game","editor"},
{},
{},
process_animation_func, "render", {}, false);

void process_animation_func()
{
  ecs::perform_system(process_animation_descr, process_animation);
}

void debug_physics_func();

ecs::SystemDescription debug_physics_descr("debug_physics", {
  {ecs::get_type_description<PhysicalObject>("physics"), false},
  {ecs::get_type_description<Transform>("transform"), true},
  {ecs::get_type_description<Settings>("settings"), false}
}, {
}, {"game","editor"},
{},
{},
debug_physics_func, "render", {}, false);

void debug_physics_func()
{
  ecs::perform_system(debug_physics_descr, debug_physics);
}

void render_box_collider_func();

ecs::SystemDescription render_box_collider_descr("render_box_collider", {
  {ecs::get_type_description<Settings>("settings"), false}
}, {
}, {"game"},
{"render_sky_box"},
{"process_mesh_position"},
render_box_collider_func, "render", {}, false);

void render_box_collider_func()
{
  ecs::perform_system(render_box_collider_descr, render_box_collider);
}


