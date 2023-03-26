#include "physical_object.h"
#include "bulletutil.h"

PhysicalObject::~PhysicalObject()
{
  for(auto elem : rigidBodies) {
    delete elem;
  }
  for(auto elem : constraints){
    world->removeConstraint(elem);
    delete elem;
  }
  constraints.clear();
  rigidBodies.clear();
}

btDiscreteDynamicsWorld *PhysicalObject::get_world() const
{
  return world;
}

const std::vector<RigidBody *> &PhysicalObject::getBodies() const
{
  return rigidBodies;
}

vec3 PhysicalObject::getGlPosition() const
{
  btTransform tr;
  rigidBodies[0]->getMotionStateTransform();
  return bt2glm(tr.getOrigin());
}

void PhysicalObject::setFromGlTransform(const Transform &transform)
{
  btTransform tr;
  tr.setIdentity();

  tr.setRotation(glm2bt_q(glm::quat_cast(transform.get_rotation())));
  tr.setOrigin(glm2bt(transform.get_position()));


  btRigidBody *root = getRoot();
  root->setWorldTransform(tr);
  root->getMotionState()->setWorldTransform(tr);
}