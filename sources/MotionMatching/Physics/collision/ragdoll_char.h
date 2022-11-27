#include "serialization/reflection.h"
#include <3dmath.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include "Physics/physical_object.h"
#include <transform.h>

class RagdollChar {
public:
  REFLECT(RagdollChar,
          (float) (mass))
  const bool isStatic = false;
  RagdollChar();

  void init_physical_object(const Transform &,
                            std::vector<btCollisionShape *> &,
                            std::vector<btRigidBody *> &,
                            std::vector<btTypedConstraint *> &,
                            vec3 &shift) const;
};