#pragma once

#include <3dmath.h>
#include <vector>
#include "Physics/physical_object.h"
#include "transform.h"


struct IBodyProvider
{
  virtual ~IBodyProvider() = default;

  virtual RigidBody *createBody(PhysicalObject& owner,
                                const mat4x4 &mat,
                                std::vector<btTypedConstraint *> &pointerHolder) const {};
};