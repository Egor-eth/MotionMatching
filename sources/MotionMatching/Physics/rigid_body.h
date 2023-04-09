#ifndef MOTIONMATCHING_RIGID_BODY_H
#define MOTIONMATCHING_RIGID_BODY_H
#include "btBulletDynamicsCommon.h"
#include "bulletutil.h"

class PhysicalObject;

class RigidBody {
public:
  RigidBody(PhysicalObject &owner, btCollisionShape * shapes, btTransform ownerTransform, btTransform relativeTr = createIdentity(), float mass = 0.0f, btVector3 shift = {0, 0, 0});
  ~RigidBody();

  RigidBody(const RigidBody&) = delete;
  RigidBody &operator=(const RigidBody&) = delete;

  PhysicalObject &getOwner() const;
  btTransform &getTransform();
  const btTransform &getTransform() const;
  btTransform getMotionStateTransform() const;
  const btTransform &getRelativeTransform() const;
  btRigidBody *get();
  const btRigidBody *get() const;
  operator btRigidBody*();
  operator const btRigidBody*() const;
  const btRigidBody *operator->() const;
  btRigidBody *operator->();
  const btVector3 &getShift() const {
    return glShift;
  }
private:
  btVector3 glShift;
  btRigidBody* body;
  btTransform relativeTransform;
  PhysicalObject &owner;
};


#endif
