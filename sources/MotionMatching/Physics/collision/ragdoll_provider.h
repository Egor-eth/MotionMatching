#pragma once
#include "body_provider.h"
#include <bullet/btBulletDynamicsCommon.h>
#include "Animation/animation_player.h"
#include "serialization/reflection.h"
#include <transform.h>
#include <unordered_map>

class RagdollProvider {
public:
  REFLECT(RagdollProvider,
          //(std::vector<std::string>) (endNodes),
          (vec2) (diag),
          (float) (linDamping),
          (float) (angDamping),
          (float) (restitution),
          (float) (friction),
          (float) (mass));
  std::vector<std::string> endNodes;

  RagdollProvider();

  void create(PhysicalObject &owner,
              AnimationPlayer &animPlayer,
              const Transform &rootTransform,
              std::unordered_map<int, RigidBody*> &bodies,
              std::vector<btTypedConstraint*> &constraints) const;
private:
  void create_recursive(PhysicalObject &,
                        AnimationTree &tree,
                        unsigned int nodeId,
                        const Transform &rootTransform,
                        std::unordered_map<int, RigidBody*> &bodies,
                        std::vector<btTypedConstraint*> &constraints) const;
};

