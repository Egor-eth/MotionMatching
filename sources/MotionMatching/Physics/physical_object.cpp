#include "physical_object.h"
#include "bulletutil.h"

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

vec3 PhysicalObject::getGlPosition() const
{
  return bt2glm(rigidBodies[0]->getCenterOfMassPosition()) - shift;
}

void PhysicalObject::setFromGlTransform(const Transform &transform)
{
  btTransform tr;
  tr.setIdentity();

  tr.setRotation(glm2bt_q(glm::quat_cast(transform.get_rotation())));
  tr.setOrigin(glm2bt(transform.get_position() + shift));

  btRigidBody *root = getRoot();
  root->setWorldTransform(tr);
  root->getMotionState()->setWorldTransform(tr);
}