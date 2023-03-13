#include "ragdoll_char.h"
/*
RagdollChar::RagdollChar()
        : mass(10.0f)
{

}

void RagdollChar::init_physical_object(const Transform &tr,
                                        std::vector<btCollisionShape *> &collisionShapes,
                                        std::vector<btRigidBody *> &rigidBodies,
                                        std::vector<btTypedConstraint *> &,
                                        vec3 &glShift) const
{
  /*
  btTransform transform;
  btCollisionShape *boxShape = new btBoxShape(glm2bt(size));
  btCompoundShape *shape = new btCompoundShape();

  transform.setIdentity();
  transform.setOrigin(glm2bt({0, 0, 0}));
  shape->addChildShape(transform, boxShape);
  collisionShapes.push_back(shape);
  collisionShapes.push_back(boxShape);

  glShift = -shift;

  transform.setFromOpenGLMatrix(glm::value_ptr(tr.get_transform()));
  btRigidBody *body = isStatic ? create_static_rigid_body(shape, transform) : create_dynamic_rigid_body(shape, transform, mass);
  rigidBodies.push_back(body);

}*/