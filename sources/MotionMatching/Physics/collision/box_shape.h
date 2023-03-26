#pragma once
#include "serialization/reflection.h"
#include <3dmath.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include "Physics/physical_object.h"
#include <transform.h>

class BoxShape {
public:
  REFLECT(BoxShape,
          (vec3) (size),
          (vec3) (shift),
          (float) (mass),
          (bool) (isStatic),
          (bool) (zeroInvInertiaX),
          (bool) (zeroInvInertiaY),
          (bool) (zeroInvInertiaZ),
          (float) (linDamping),
          (float) (angDamping),
          (float) (restitution),
          (float) (friction))

  BoxShape();

  void init_physical_object(PhysicalObject& owner,
                            const Transform &,
                            std::vector<RigidBody *> &,
                            std::vector<btTypedConstraint *> &,
                            vec3 &shift) const;
};

