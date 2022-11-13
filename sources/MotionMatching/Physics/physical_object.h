#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include <transform.h>

class PhysicalObject {
public:
  ~PhysicalObject();

  template<typename T>
  void init(btDiscreteDynamicsWorld *w, const Transform &tr, const T& obj)
  {
    world = w;
    obj.init_physical_object(tr, collisionShapes, rigidBodies, constraints);
    for(auto body : rigidBodies) {
      world->addRigidBody(body);
    }
    for(auto constraint : constraints) {
      world->addConstraint(constraint, true);
    }
  }

  btDiscreteDynamicsWorld *get_world() const;
  const std::vector<btRigidBody *> &getBodies() const;
private:
  btDiscreteDynamicsWorld *world;
  std::vector<btCollisionShape *> collisionShapes;
  std::vector<btRigidBody *> rigidBodies;
  std::vector<btTypedConstraint *> constraints;

};
