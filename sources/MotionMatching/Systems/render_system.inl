#include <ecs.h>
#include <algorithm>
#include "Animation/animation_player.h"
#include <transform.h>
#include <render/render.h>
#include <render/debug_arrow.h>
#include <render/global_uniform.h>
#include "Animation/settings.h"
#include "Physics/collision/body_generator.h"
#include "Physics/bulletutil.h"
#include "resources/resources.h"
#include "profiler/profiler.h"
#include "Physics/world.h"


SYSTEM(stage=render;scene=game, editor) process_animation(
  const Asset<Mesh> &mesh,
  const AnimationPlayer &animationPlayer,
  Transform &transform,
  const Settings &settings)
{
  if (mesh)
  {
    std::vector<mat4> &curTransform = transform.get_bones();
    const AnimationTree &tree = animationPlayer.tree;
  
    curTransform.resize(mesh->bonesMap.size());
    for (uint i = 0, n = std::min(tree.nodes.size(), animationPlayer.treeBoneToMesh.size()); i < n; i++)
    {
      int idx = animationPlayer.treeBoneToMesh[i];
      if (idx >= 0 && idx < (int)curTransform.size())
        curTransform[idx] = tree.get_bone_transform(i);
    }
  }
  if (settings.debugBones)
  {
    mat4 t = transform.get_transform();
    const AnimationTree &tree = animationPlayer.tree;
    static std::vector<vec3> boneOffsets;
    if (boneOffsets.size() != tree.nodes.size())
      boneOffsets.resize(tree.nodes.size());

    for (uint i = 0; i < tree.nodes.size(); i++)
    {
      boneOffsets[i] = vec3(tree.get_transform(i)[3]);
    }
    for (uint i = 0; i < tree.nodes.size(); i++)
    {
      vec3 p = tree.nodes[i].parent() >= 0 ? boneOffsets[tree.nodes[i].parent()] : vec3(0.f);
      float width = std::min(0.5f, length(boneOffsets[i] - p) * 0.05f);
      draw_arrow(t, p, boneOffsets[i], vec3(0,0.8f,0), width);
    }
  }
  AnimationLerpedIndex index = animationPlayer.get_motion_matching() ? animationPlayer.get_motion_matching()->get_index() : animationPlayer.get_index();

  if (!index)
    return;
  mat4 transformation = transform.get_transform();

  const NodeFeatures& feature = index.current_index().get_feature();
  
  //vec3 man = transformation * vec4(feature.nodes[(int)AnimationFeaturesNode::Hips], 1.f);
  //Ray ray(man, vec3(0,-1,0), 100);
  //Collision collision = ray_cast(ray);
  //draw_arrow(ray.from, collision.collisionPoint, vec3(10,0,0), 0.04f, false);

  if (settings.debugNodes)
  {
    #define DEBUG_NODE(node)\
    {\
      vec3 p = vec3(transformation * vec4(feature.nodes[(int)node], 1.f));\
      vec3 v = vec3(transformation * vec4(feature.nodesVelocity[(int)node], 0.f));\
      draw_arrow(p, p + v * 0.5f, vec3(1,0,0), 0.02f, false);\
    }

    DEBUG_NODE(AnimationFeaturesNode::LeftToeBase)
    DEBUG_NODE(AnimationFeaturesNode::LeftHand)
    DEBUG_NODE(AnimationFeaturesNode::RightToeBase)
    DEBUG_NODE(AnimationFeaturesNode::RightHand)
  }

/* 
  if (false)
  {
    u8 onGround = index.current_index().get_clip().onGround[index.current_index().get_cadr_index()];
    onGround = animationPlayer.onGround;
    if (onGround & 1)
    {
      material->set_property(Property("Ambient", vec3(1,0,0)));
      debugTransform.set_scale(vec3(0.11f));
      
      debugTransform.get_position() = transformation * vec4(feature.nodes[(int)AnimationFeaturesNode::LeftToeBase], 1.f);
      debugGoalSphere.render(debugTransform, true);
    }
    if (onGround & 2)
    {
      material->set_property(Property("Ambient", vec3(1,0,0)));
      debugTransform.set_scale(vec3(0.11f));
      
      debugTransform.get_position() = transformation * vec4(feature.nodes[(int)AnimationFeaturesNode::RightToeBase], 1.f);
      debugGoalSphere.render(debugTransform, true);
    }
  } */
  if (settings.debugTrajectory)
  {
    constexpr float dirLength = 0.3f;
    constexpr vec3 colors[2] = {vec3(0,1,0), vec3(1,0,0)};
    const AnimationTrajectory &trajectory = index.current_index().get_trajectory();

    const std::array<TrajectoryPoint, AnimationTrajectory::PathLength> *trajectories[2] = {&trajectory.trajectory, &animationPlayer.inputGoal.feature.trajectory.trajectory};
    for(int i = 0; i < 2; i++)
    {
      for (const TrajectoryPoint &p: *trajectories[i])
      {
        vec3 v = vec3(transformation * vec4(p.point * 2.f, 1.f));
        vec3 w = vec3(transformation * vec4(p.velocity * dirLength, 0.f));
        draw_arrow(v, v + w, colors[i], 0.02f, false);
      }
    }
  }
}

SYSTEM(stage=render;scene=game, editor) debug_physics(
        const PhysicalObject &physics,
        const Transform *transform,
        const Settings &settings)
{
  if(settings.debugCollision) {
 /*  for(auto body : physics.getBodies()) {
     btVector3 a, b;
     body->getAabb(a, b);
     vec3 v = bt2glm(a);
     vec3 w = bt2glm(b);
     draw_arrow(v, w, vec3(0.8, 0, 0.8), 0.05f, false);
   }*/
  }
}

template<typename Callable>
void find_box_shapes(Callable);

//Need to shift hitboxes by right value
SYSTEM(stage=render; after=process_mesh_position; before=render_sky_box; scene=game) render_box_collider(
        const Settings &settings)
{
  if (!settings.debugCollision)
    return;


  Asset<Mesh> cube = cube_mesh(false);
  Asset<Material> collisionMat = get_resource<Material>("collision");
  if (!cube || !collisionMat)
    return;

  UniformBuffer &dynamicTransforms = get_buffer("DynamicTransforms");
  constexpr uint instanceSize = sizeof(mat3x4);
  uint instanceCount = 0;
  QUERY()find_box_shapes([&](const PhysicalObject &physics)
                                {
                                    for(auto &p : physics.getBodies()) {
                                      RigidBody &body = *p.second;
                                      mat4x4 buf = mat4x4(1);
                                      mat3x4 *buffer = (mat3x4*)dynamicTransforms.get_buffer(instanceCount * instanceSize, instanceSize);

                                      Transform tm;
                                      btTransform tr = body.getMotionStateTransform();
                                      vec3 pos = bt2glm(tr.getOrigin());

                                      BoundingBox bbox = getBoundingBox(body);

                                      vec3 size = bbox.diagonal() / 2.0f;
                                      if(!body->isStaticObject()) {
                                        pos.y += size.y;
                                      }
                                      //vec3 shift = bt2glm(body.getShift());
                                      //shift = glm::mat3_cast(getRotation(tr)) * shift;
                                      //pos -= shift;

                                      tm.set_position(pos);
                                      tm.set_rotation(getRotation(tr));
                                      tm.set_scale(size);

                                      *buffer = tm.get_3x4transform();
                                      instanceCount++;
                                    }
                                });
  if (instanceCount == 0) return;
  const Shader &shader = get_shader("collision_shader");
  if(!shader) return;

  ProfilerLabelGPU label("bounding_box");
  dynamicTransforms.bind();
  shader.use();
  dynamicTransforms.flush_buffer(instanceCount * instanceSize);
  cube->render_instances(instanceCount, true);
}