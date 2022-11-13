#pragma once
#include "bt2glm.h"

btRigidBody* create_static_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform);

btRigidBody* create_dynamic_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform, btScalar mass);