#include "bulletutil.h"

btRigidBody* create_static_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform)
{
  btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(0.0f, motionState, collisionShape);
  btRigidBody* body = new btRigidBody(constructionInfo);

  return body;
}

btRigidBody* create_dynamic_rigid_body (btCollisionShape* collisionShape, const btTransform& startTransform, btScalar mass)
{
  btVector3 localInertia(0.0f, 0.0f, 0.0f);
  collisionShape->calculateLocalInertia(mass, localInertia);


  btDefaultMotionState* motionState = new btDefaultMotionState(startTransform);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, collisionShape, localInertia);
  btRigidBody* body = new btRigidBody(constructionInfo);
  return body;
}

btTransform &getTransform(btRigidBody *body)
{
  if (body->getMotionState()) {
    btTransform tr;
    body->getMotionState()->getWorldTransform(tr);
    return tr;
  }
   return body->getWorldTransform();
}

const btTransform &getTransform(const btRigidBody *body)
{
  if (body->getMotionState()) {
    btTransform tr;
    body->getMotionState()->getWorldTransform(tr);
    return tr;
  }
  return body->getWorldTransform();
}

mat4x4 getGLTransform(const btRigidBody *body)
{
  const btTransform tr = getTransform(body);
  mat4x4 mat;
  tr.getOpenGLMatrix(glm::value_ptr(mat));
  return mat;
}

quat getRotation(const btTransform &transform) {
  return bt2glm_q(transform.getRotation());
}

BoundingBox getBoundingBox(const btRigidBody *body)
{
  btVector3 a, b;
  body->getCollisionShape()->getAabb(createIdentity(), a, b);
  //body->getAabb(a, b);
  return {bt2glm(a), bt2glm(b)};
}

btTransform createIdentity()
{
  btTransform tr;
  tr.setIdentity();
  return tr;
}
