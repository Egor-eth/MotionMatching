#include "physical_object.h"

PhysicalObject::~PhysicalObject()
{
  for(auto elem : constraints){
    world->removeConstraint(elem);
    delete elem;
  }
  for(auto elem : rigidBodies) {
    world->removeRigidBody(elem);
    delete elem->getMotionState();
    delete elem;
  }
  for(auto elem : collisionShapes) delete elem;
  constraints.clear();
  rigidBodies.clear();
  collisionShapes.clear();
}

btDiscreteDynamicsWorld *PhysicalObject::get_world() const
{
  return world;
}

const std::vector<btRigidBody *> &PhysicalObject::getBodies() const
{
  return rigidBodies;
}
