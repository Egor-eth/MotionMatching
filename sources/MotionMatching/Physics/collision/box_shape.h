#pragma once
#include "body_provider.h"
#include <bullet/btBulletDynamicsCommon.h>

class BoxShape : public IBodyProvider {
public:
  vec3 size;
  vec3 shift;
  float mass;
  bool zeroInvInertiaX;
  bool zeroInvInertiaY;
  bool zeroInvInertiaZ;
  float linDamping;
  float angDamping;
  float restitution;
  float friction;

  BoxShape();

  RigidBody *createBody(PhysicalObject& owner,
                        const mat4x4 &,
                        std::vector<btTypedConstraint *> &) const override;
};

