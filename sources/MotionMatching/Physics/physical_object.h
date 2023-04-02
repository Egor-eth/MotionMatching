#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include <vector>
#include "unordered_map"
#include <transform.h>
#include "rigid_body.h"
#include "world.h"
#include "collision/body_provider.h"

class PhysicalObject {
public:
  ~PhysicalObject();

  void init(World &world, bool isSimple, std::unordered_map<int, RigidBody*> rigidBodies, std::vector<btTypedConstraint*> constraints);

  RigidBody &operator[](int idx);

  const RigidBody &operator[](int idx) const;

  const size_t numBones() const;

  btDiscreteDynamicsWorld *get_world() const;
  const std::unordered_map<int, RigidBody*> &getBodies() const;

  RigidBody &getRoot()
  {
    return *rigidBodies[0];
  }

  bool isSsimple() {
    return simple;
  }

  vec3 getGlPosition() const;

  void setFromGlTransform(const Transform &);

private:
  bool simple = true;
  btDiscreteDynamicsWorld *world;
  std::unordered_map<int, RigidBody*> rigidBodies;
  std::vector<btTypedConstraint*> constraints;
};
