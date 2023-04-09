#include "box_shape.h"
#include "Physics/rigid_body.h"
#include "Physics/bulletutil.h"
#include "Physics/collision/shape_pool.h"
#include <ecs_core.h>


BoxShape::BoxShape()
  : IBodyProvider(), size({0, 0, 0}), shift({0, 0, 0}), mass(),
    zeroInvInertiaX(false), zeroInvInertiaY(false), zeroInvInertiaZ(false),
    angDamping(0.0f), linDamping(0.0f), restitution(0.0f), friction(0.0f)
{

}

RigidBody *BoxShape::createBody(PhysicalObject &owner,
                                const mat4x4 &mat,
                                std::vector<btTypedConstraint *> &) const
{
  Transform tr(mat);
  btTransform transform;

  const vec3 sz = size / 2.0f;
  const vec3 center_shift = {0, sz.y * tr.get_scale().y, 0};
  const vec3 full_shift = shift + center_shift;

  ShapePool &pool = ecs::get_singleton<ShapePool>();

  btCollisionShape *shape = pool.shiftedShape(pool.getBoxShape(glm2bt(size), glm2bt(tr.get_scale())),
                                              glm2bt(full_shift));

  transform.setIdentity();
  transform.setOrigin(glm2bt(tr.get_position() + shift));
  transform.setRotation(glm2bt_q(glm::quat_cast(tr.get_rotation())));

  btTransform relativeTr = createIdentity();
  //relativeTr.setOrigin(glm2bt(full_shift));
  RigidBody *body = new RigidBody(owner, shape, transform, relativeTr, mass, glm2bt(full_shift));
  RigidBody &ref = *body;
  btVector3 revInv = ref->getInvInertiaDiagLocal();
  if(zeroInvInertiaX) revInv.setX(0.0f);
  if(zeroInvInertiaY) revInv.setY(0.0f);
  if(zeroInvInertiaZ) revInv.setZ(0.0f);
  ref->setInvInertiaDiagLocal(revInv);

  ref->setFriction(friction);
  ref->setDamping(linDamping, angDamping);
  ref->setRestitution(restitution);

  return body;
}

