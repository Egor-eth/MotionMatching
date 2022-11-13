

set(MODULE_SOURCES )
set(MODULE_C_SOURCES MotionMatching/Physics/ragdoll.cpp MotionMatching/Physics/ragdoll.h MotionMatching/Physics/collision/box_shape.cpp MotionMatching/Physics/collision/static_box.h MotionMatching/Physics/physical_object.cpp MotionMatching/Physics/physical_object.h MotionMatching/Physics/collision/character_body.cpp MotionMatching/Physics/collision/character_body.h MotionMatching/Physics/bt2glm.cpp MotionMatching/Physics/bt2glm.h MotionMatching/Physics/bulletutil.cpp MotionMatching/Physics/world.cpp MotionMatching/Physics/world.h)

file(GLOB_RECURSE MODULE_SOURCES ${MODULE_PATH}/*.cpp)
file(GLOB_RECURSE MODULE_C_SOURCES ${MODULE_PATH}/*.c)
include_directories(${MODULE_PATH})

add_library(${MODULE_NAME} OBJECT ${MODULE_SOURCES} ${MODULE_C_SOURCES})
