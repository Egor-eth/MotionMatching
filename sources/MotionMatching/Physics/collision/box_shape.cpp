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
  vec3 sz = size / 2.0f;
  btTransform transform;
  btCollisionShape *boxShape = new btBoxShape(glm2bt(sz));
  boxShape->setLocalScaling(glm2bt(tr.get_scale()));
  btCompoundShape *shape = new btCompoundShape();

  float center_shift = sz.y * tr.get_scale().y;

  vec3 full_shift = shift;
  if(!isStatic) {
    full_shift.y += center_shift; // ?
  }

  transform.setIdentity();
  transform.setOrigin(glm2bt(full_shift));
  shape->addChildShape(transform, boxShape);
  collisionShapes.push_back(shape);
  collisionShapes.push_back(boxShape);

  glShift = {0, 0 ,0};// full_shift;

  transform.setIdentity();
  transform.setOrigin(glm2bt(tr.get_position() + full_shift));
  transform.setRotation(glm2bt_q(glm::quat_cast(tr.get_rotation())));
  btRigidBody *body = isStatic ?
          create_static_rigid_body(shape, transform) :
          create_dynamic_rigid_body(shape, transform, mass);
  rigidBodies.push_back(body);
}

