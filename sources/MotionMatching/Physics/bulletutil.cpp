#include "bulletutil.h"

btRigidBody* create_static_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform)
{
  btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(0.0f, motionState, collisionShape);
  constructionInfo.m_additionalDamping = true; //?
  btRigidBody* body = new btRigidBody(constructionInfo);

  return body;
}

btRigidBody* create_dynamic_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform, btScalar mass)
{
  btVector3 localInertia(0.0f, 0.0f, 0.0f);
  collisionShape->calculateLocalInertia(mass, localInertia);


  btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, collisionShape, localInertia);
  constructionInfo.m_additionalDamping = true; //?
  btRigidBody* body = new btRigidBody(constructionInfo);

  return body;
}