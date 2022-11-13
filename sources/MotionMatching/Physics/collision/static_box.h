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
          (float) (mass))

  void init_physical_object(const Transform &,
                            std::vector<btCollisionShape *> &,
                            std::vector<btRigidBody *> &,
                            std::vector<btTypedConstraint *> &) const;
};

