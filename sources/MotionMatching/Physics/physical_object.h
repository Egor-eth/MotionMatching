#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include <transform.h>
#include "rigid_body.h"

class PhysicalObject {
public:
  ~PhysicalObject();

  template<typename T>
  void init(btDiscreteDynamicsWorld *w, const Transform &tr, const T& obj)
  {
    world = w;
    obj.init_physical_object(*this, tr, rigidBodies, constraints, shift);
    for(auto body : rigidBodies) {
      world->addRigidBody(body->get());
    }
    for(auto constraint : constraints) {
      world->addConstraint(constraint, true);
    }
    for(auto body : rigidBodies) {
      body->get()->setRestitution(0.0f);
      body->get()->setFriction(0.0f);
      body->get()->forceActivationState(ACTIVE_TAG);
      body->get()->activate();
    }
  }

  btDiscreteDynamicsWorld *get_world() const;
  const std::vector<RigidBody*> &getBodies() const;

  RigidBody &getRoot()
  {
    return *rigidBodies[0];
  }

  const btTransform &getRootTransform() {
    return rigidBodies[0]->getTransform();
  }

  vec3 getGlPosition() const;
  void setFromGlTransform(const Transform &);

private:
  btDiscreteDynamicsWorld *world;
  std::vector<RigidBody*> rigidBodies;
  std::vector<btTypedConstraint*> constraints;
  vec3 shift;
};
