#ifndef MOTIONMATCHING_RIGID_BODY_H
#define MOTIONMATCHING_RIGID_BODY_H
#include "btBulletDynamicsCommon.h"
#include "bulletutil.h"
#include <vector>

class PhysicalObject;

class RigidBody {
public:
  RigidBody(PhysicalObject &owner, std::vector<btCollisionShape *> shapes, btTransform ownerTransform, btTransform relativeTr = createIdentity(), float mass = 0.0f);
  ~RigidBody();
  PhysicalObject &getOwner() const;
  btTransform &getTransform();
  btTransform getMotionStateTransform() const;
  const btTransform &getRelativeTransform() const;
  btRigidBody *get();
  const btRigidBody *get() const;
  operator btRigidBody*();
  operator const btRigidBody*() const;
  const btRigidBody *operator->() const;
  btRigidBody *operator->();
private:
  btRigidBody* body;
  btTransform relativeTransform;
  std::vector<btCollisionShape *> shapes;
  PhysicalObject &owner;
};


#endif
