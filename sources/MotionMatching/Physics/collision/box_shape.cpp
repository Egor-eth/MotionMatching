#include "static_box.h"
#include "Physics/bulletutil.h"

void BoxShape::init_physical_object(const Transform &tr,
                                    std::vector<btCollisionShape *> &collisionShapes,
                                    std::vector<btRigidBody *> &rigidBodies,
                                    std::vector<btTypedConstraint *> &) const
{
  btCollisionShape *shape = new btBoxShape(glm2bt(size));
  collisionShapes.push_back(shape);

  btTransform transform;
  transform.setIdentity();
  transform.setFromOpenGLMatrix(value_ptr(tr.get_transform()));
  btRigidBody *body = mass > 0 ? create_dynamic_rigid_body(shape, transform, mass) : create_static_rigid_body(shape, transform);
  rigidBodies.push_back(body);

}

