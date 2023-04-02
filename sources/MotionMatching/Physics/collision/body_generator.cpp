#include "body_generator.h"
#include "box_shape.h"
#include "common.h"

BodyGenerator::BodyGenerator()
  : type(""), size({0, 0, 0}), shift({0, 0, 0}), mass(),
    zeroInvInertiaX(false), zeroInvInertiaY(false), zeroInvInertiaZ(false),
    angDamping(0.0f), linDamping(0.0f), restitution(0.0f), friction(0.0f)
{

}

BodyGenerator::~BodyGenerator()
{
}

RigidBody *BodyGenerator::createBody(PhysicalObject& owner,
                                     const mat4x4 &tr,
                                     std::vector<btTypedConstraint *> &constraints) const
{
  IBodyProvider *shape = nullptr;
  if(type == "box") {
    BoxShape* bshape = new BoxShape();
    bshape->size = size;
    bshape->shift = shift;
    bshape->mass = mass;
    bshape->friction = friction;
    bshape->restitution = restitution;
    bshape->angDamping = angDamping;
    bshape->linDamping = linDamping;
    bshape->zeroInvInertiaX = zeroInvInertiaX;
    bshape->zeroInvInertiaY = zeroInvInertiaY;
    bshape->zeroInvInertiaZ = zeroInvInertiaZ;
    shape = bshape;
  } else {
    debug_error("Unknown shape (%s)", type.c_str());
  }

  if(shape != nullptr) {
    return shape->createBody(owner, tr, constraints);
  }
  return nullptr;
}