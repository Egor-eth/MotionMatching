#include "box_shape.h"
#include "Physics/bulletutil.h"


BoxShape::BoxShape()
  : size({0, 0, 0}), shift({0, 0, 0}), mass(), isStatic()
{

}

void BoxShape::init_physical_object(const Transform &tr,
                                    std::vector<btCollisionShape *> &collisionShapes,
                                    std::vector<btRigidBody *> &rigidBodies,
                                    std::vector<btTypedConstraint *> &,
                                    vec3 &glShift) const
{
  btTransform transform;
  btCollisionShape *boxShape = new btBoxShape(glm2bt(size));
  boxShape->setLocalScaling(glm2bt(tr.get_scale()));
  btCompoundShape *shape = new btCompoundShape();

  vec3 sz = vec3(tr.get_transform() * vec4(size, 0));

  Transform tmp;
  vec3 full_shift = shift;
  full_shift.y += sz.y; // ?

  tmp.set_position(full_shift);

  transform.setFromOpenGLMatrix(glm::value_ptr(tmp.get_transform()));
  shape->addChildShape(transform, boxShape);
  collisionShapes.push_back(shape);
  collisionShapes.push_back(boxShape);

  glShift = full_shift;


  tmp = tr;
  tmp.set_scale({1, 1, 1});
  transform.setIdentity();
  transform.setFromOpenGLMatrix(glm::value_ptr(tmp.get_transform()));
  btRigidBody *body = isStatic ?
          create_static_rigid_body(shape, transform) :
          create_dynamic_rigid_body(shape, transform, mass);
  rigidBodies.push_back(body);
}

