#include "character_body.h"
#include "Physics/bulletutil.h"

void CharacterBody::init_physical_object(const Transform &tr,
                                         std::vector<btCollisionShape *> &collisionShapes,
                                         std::vector<btRigidBody *> &rigidBodies,
                                         std::vector<btTypedConstraint *> &) const
{
  btCollisionShape *shape = new btBoxShape(glm2bt(size / 2.0f));
  collisionShapes.push_back(shape);

  btTransform transform(glm2bt(tr.get_rotation()), glm2bt(tr.get_position()));
  //transform.setIdentity();
  rigidBodies.push_back(create_static_rigid_body(shape, transform));
}

