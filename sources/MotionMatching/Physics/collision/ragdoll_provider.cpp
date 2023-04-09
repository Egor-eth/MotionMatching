#include "ragdoll_provider.h"
#include "Physics/bulletutil.h"
#include "box_shape.h"
#include "3dmath.h"
#include "shape_pool.h"

RagdollProvider::RagdollProvider()
  : endNodes({}), diag({0.1f, 0.1f}),
    linDamping(0.0f), angDamping(0.0f), restitution(0.0f), friction(0.0f), mass(1.0f)
{

}

namespace {
  std::pair<btCollisionShape *, mat4x4> boxFromBone(const vec3 &v, const vec3 &diag)
  {
    const float len = glm::length(v);
    const vec3 h = {0, len, 0}; //vertical vector with length of v
    vec3 h_r = h;
    if(v.y < 0.0f) {
      h_r.y *= -1;
    }

    mat4x4 transform = glm::mat4_cast(quat(glm::normalize(h_r), glm::normalize(v)));

    if(v.y < 0) {
      transform = glm::translate(mat4x4(1.0f), h_r) * transform;
    }

    float mul = min(len * 0.1f, glm::length(diag)) / glm::length(diag);


    const btVector3 sz = glm2bt(h + diag * mul); //box half diag

    ShapePool &pool = ecs::get_singleton<ShapePool>();

    //vertical boxShape for body
   return {pool.shiftedShape(pool.getBoxShape(sz), {0.0f, sz.y(), 0.0f}), transform};
  }
}

void RagdollProvider::create_recursive(PhysicalObject &owner,
                      AnimationTree &tree,
                      unsigned int nodeId,
                      const Transform &rootTransform,
                      std::unordered_map<int, RigidBody*> &bodies,
                      std::vector<btTypedConstraint*> &constraints) const
{

  static std::vector<vec3> boneOffsets;
  if (boneOffsets.size() != tree.nodes.size()) {
    boneOffsets.resize(tree.nodes.size());

    for (uint i = 0; i < tree.nodes.size(); i++) {
      boneOffsets[i] = vec3(tree.get_transform(i)[3]);
    }
  }


  const AnimationNode &node = tree.nodes[nodeId];
  RigidBody *body;

    vec3 parent_pos = node.parent() >= 0 ? boneOffsets[node.parent()] : vec3(0.0f);
    const vec3 bone_vec = boneOffsets[nodeId] - parent_pos;
    auto p = boxFromBone(bone_vec, {diag.x, 0, diag.y});

    mat4x4 parentTransform = node.parent() >= 0 ? tree.get_transform(node.parent()) : mat4x4(1.0f);


    const mat4x4 bodyTransform = //rootTransform.get_transform() * parentTransform;// * glm::mat4_cast(p.second);
             glm::translate(rootTransform.get_transform(), parent_pos) * p.second;// * mat4(Transform(tree.get_transform(nodeId)).get_rotation());

    btTransform tr;
    tr.setIdentity();
    tr.setFromOpenGLMatrix(glm::value_ptr(bodyTransform));

    float m = mass;
    if(node.parent() >= 0) {
      const auto &pName = tree.nodes[node.parent()].get_name();
      if(pName == "LeftHand" || pName=="RightHand") {
        m *= 0.2f;
      }
    } else if(node.get_name() == "Spine") {
      m *= 4;
    }

    body = new RigidBody(owner, p.first, tr, createIdentity(), m);



    btTransform localA = createIdentity();
    btTransform localB = createIdentity();

    localA.setOrigin({0.0f, 0.0f, 0.0f});

    //localB.getBasis().setEulerZYX(SIMD_HALF_PI,0,-SIMD_HALF_PI);
    localB.setOrigin(glm2bt(-bone_vec) * 0.6f);

    if(node.parent() >= 0) {
      btTypedConstraint *constraint = new btGeneric6DofConstraint(*bodies[node.parent()]->get(), *body->get(), localA,
                                                                  localB, true);
      constraints.push_back(constraint);
    }
  //}
  RigidBody *ref = body;
  ref->get()->setFriction(friction);
  ref->get()->setDamping(linDamping, angDamping);
  ref->get()->setRestitution(restitution);

  bodies[nodeId] = body;
  if(std::find(endNodes.begin(), endNodes.end(), node.get_name()) == endNodes.end()) {
    for(int i : node.get_data().childs) {
      create_recursive(owner, tree, i, rootTransform, bodies, constraints);
    }
  }
}


void RagdollProvider::create(PhysicalObject &owner,
                             AnimationPlayer &animPlayer,
                             const Transform &rootTransform,
                             std::unordered_map<int, RigidBody*> &bodies,
                             std::vector<btTypedConstraint*> &constraints) const
{
  create_recursive(owner, animPlayer.tree, 0, rootTransform, bodies, constraints);
}

