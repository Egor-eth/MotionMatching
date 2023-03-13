#include "rigid_body.h"

RigidBody::RigidBody(PhysicalObject &owner, std::vector<btCollisionShape *>shapes, const btTransform &ownerTransform, const btTransform &relativeTr, float mass)
  : body(), shapes(shapes), relativeTransform(relativeTr), owner(owner)
{
  btCollisionShape *shape = shapes[0];
  btTransform tr = ownerTransform * relativeTr;
  btVector3 localInertia(0.0f, 0.0f, 0.0f);

  if(mass != 0.0f) {
    shape->calculateLocalInertia(mass, localInertia);
  }


  btDefaultMotionState* motionState = new btDefaultMotionState(tr);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
  body = new btRigidBody(constructionInfo);
  if(mass == 0.0f) {
    body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
  }

  btVector3 inv_inertia = body->getInvInertiaDiagLocal();
  inv_inertia.setX(0.0f);
  inv_inertia.setZ(0.0f);
  body->setInvInertiaDiagLocal(inv_inertia);
}

RigidBody::~RigidBody()
{
  delete body->getMotionState();
  delete body;
  for(btCollisionShape *shape : shapes) {
    delete shape;
  }
}

PhysicalObject &RigidBody::getOwner() const {
  return owner;
}

btTransform &RigidBody::getTransform() {
  return body->getWorldTransform();
}

const btTransform &RigidBody::getRelativeTransform() const {
  return relativeTransform;
}

btRigidBody *RigidBody::get() {
  return body;
}

const btRigidBody *RigidBody::get() const {
  return body;
}

RigidBody::operator btRigidBody *() {
  return body;
}

RigidBody::operator const btRigidBody *() const {
  return body;
}

const btRigidBody *RigidBody::operator->() const {
  return body;
}

btRigidBody *RigidBody::operator->() {
  return body;
}
