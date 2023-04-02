#pragma once
#include "serialization/reflection.h"
#include "body_provider.h"
#include <string>
#include <3dmath.h>


struct BodyGenerator : public IBodyProvider{
public:
  REFLECT(BodyGenerator,
          (std::string) (type),
          (vec3) (size),
          (vec3) (shift),
          (float) (mass),
          (bool) (zeroInvInertiaX),
          (bool) (zeroInvInertiaY),
          (bool) (zeroInvInertiaZ),
          (float) (linDamping),
          (float) (angDamping),
          (float) (restitution),
          (float) (friction));


  BodyGenerator();
  ~BodyGenerator();
  RigidBody *createBody(PhysicalObject& owner,
                        const mat4x4 &,
                        std::vector<btTypedConstraint *> &) const override;
};
