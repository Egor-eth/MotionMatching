#include "rigid_body.h"

RigidBody::RigidBody(PhysicalObject &owner, btCollisionShape *shape, btTransform ownerTransform, btTransform relativeTr, float mass, btVector3 shift)
  : body(nullptr), relativeTransform(relativeTr), owner(owner), glShift(shift)
{
  btTransform tr = ownerTransform * relativeTr;
  btVector3 localInertia(0.0f, 0.0f, 0.0f);

  if(mass != 0.0f) {
    shape->calculateLocalInertia(mass, localInertia);
  }


  btDefaultMotionState* motionState = new btDefaultMotionState(tr);
  btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, shape, localInertia);
  body = new btRigidBody(constructionInfo);

}

RigidBody::~RigidBody()
{
  delete body->getMotionState();
  delete body;
}

PhysicalObject &RigidBody::getOwner() const
{
  return owner;
}

btTransform &RigidBody::getTransform()
{
  return body->getWorldTransform();
}

const btTransform &RigidBody::getTransform() const
{
  return body->getWorldTransform();
}

btTransform RigidBody::getMotionStateTransform() const
{
  btTransform tr;
  if(body->isStaticObject()) return body->getWorldTransform();
  body->getMotionState()->getWorldTransform(tr);
  return tr;
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
