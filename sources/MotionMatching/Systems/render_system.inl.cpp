#include "render_system.inl"
#include <ecs_perform.h>
//Code-generator production

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
  {ecs::get_type_description<BoxShape>("collision"), false},
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


