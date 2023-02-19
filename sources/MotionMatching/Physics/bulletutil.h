#pragma once
#include "bt2glm.h"
#include "transform.h"
#include "render/occlusion.h"

btRigidBody* create_static_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform);

btRigidBody* create_dynamic_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform, btScalar mass);

btTransform &getTransform(btRigidBody *);
const btTransform &getTransform(const btRigidBody *);


mat4x4 getGLTransform(const btRigidBody *body);
quat getRotation(const btTransform &transform);
BoundingBox getBoundingBox(const btRigidBody *body);