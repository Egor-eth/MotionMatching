#include "physical_object.h"
#include "bulletutil.h"
#include "stdexcept"

PhysicalObject::~PhysicalObject()
{
  for(auto &elem : rigidBodies) {
    delete elem.second;
  }
  for(auto elem : constraints){
    world->removeConstraint(elem);
    delete elem;
  }
}

void PhysicalObject::init(World &w, bool simple, std::unordered_map<int, RigidBody*> rigidBodies, std::vector<btTypedConstraint*> constraints) {
  if(!rigidBodies.contains(0)) throw std::runtime_error("PhysicalObject must contain root (0)");
  world = w;
  for(auto &p : rigidBodies) {
    RigidBody &body = *p.second;

    world->addRigidBody(body);
    body->forceActivationState(ACTIVE_TAG);
    body->activate();
  }
  for(auto constraint : constraints) {
    world->addConstraint(constraint);
  }
  this->rigidBodies = rigidBodies;
  this->constraints;
  this->simple = simple;
}

RigidBody &PhysicalObject::operator[](int idx)
{
  return *rigidBodies[idx];
}

const RigidBody &PhysicalObject::operator[](int idx) const
{
  auto it = rigidBodies.find(idx);
  return *(it->second);
}

const size_t PhysicalObject::numBones() const {
  return rigidBodies.size();
}

btDiscreteDynamicsWorld *PhysicalObject::get_world() const
{
  return world;
}

const std::unordered_map<int, RigidBody*> &PhysicalObject::getBodies() const
{
  return rigidBodies;
}

vec3 PhysicalObject::getGlPosition() const
{
  btTransform tr;
  tr = operator[](0).getMotionStateTransform();
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