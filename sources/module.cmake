

set(MODULE_SOURCES )
set(MODULE_C_SOURCES MotionMatching/Physics/ragdoll.cpp MotionMatching/Physics/ragdoll.h MotionMatching/Physics/collision/box_shape.cpp MotionMatching/Physics/collision/box_shape.h MotionMatching/Physics/physical_object.cpp MotionMatching/Physics/physical_object.h MotionMatching/Physics/collision/character_body.cpp MotionMatching/Physics/collision/character_body.h MotionMatching/Physics/bt2glm.cpp MotionMatching/Physics/bt2glm.h MotionMatching/Physics/bulletutil.cpp MotionMatching/Physics/world.cpp MotionMatching/Physics/world.h MotionMatching/Physics/debug_drawer.cpp MotionMatching/Physics/debug_drawer.h MotionMatching/Physics/rigid_body.cpp MotionMatching/Physics/rigid_body.h MotionMatching/Physics/collision/shape_provider.cpp MotionMatching/Physics/collision/shape_provider.h MotionMatching/Physics/collision/body_generator.cpp MotionMatching/Physics/collision/body_generator.h MotionMatching/Physics/collision/body_provider.h)

file(GLOB_RECURSE MODULE_SOURCES ${MODULE_PATH}/*.cpp)
file(GLOB_RECURSE MODULE_C_SOURCES ${MODULE_PATH}/*.c)
include_directories(${MODULE_PATH})

add_library(${MODULE_NAME} OBJECT ${MODULE_SOURCES} ${MODULE_C_SOURCES})
