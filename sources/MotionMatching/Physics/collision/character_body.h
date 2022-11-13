#pragma once
#include <vector>
#include <bullet/btBulletDynamicsCommon.h>
#include "serialization/reflection.h"
#include <3dmath.h>
#include <transform.h>

class CharacterBody {
  REFLECT(CharacterBody,
  (vec3) (size))

  void init_physical_object(const Transform &,
                            std::vector<btCollisionShape *> &,
                            std::vector<btRigidBody *> &,
                            std::vector<btTypedConstraint *> &) const;
};

