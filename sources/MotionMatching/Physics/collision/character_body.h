#pragma once
#include "body_provider.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "serialization/reflection.h"
#include <transform.h>


class CharacterBody {
  REFLECT(CharacterBody,
    (vec3) (size))

  void init_physical_object(PhysicalObject& owner,
                            const mat4x4 & tr,
                            std::vector<RigidBody *> & bodies,
                            std::vector<btTypedConstraint *> & constraints,
                            vec3 &shift) const;
};

