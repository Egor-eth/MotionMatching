#include <ecs.h>
#include "Animation/animation_player.h"
#include "Animation/animation_ik.h"
#include <render/debug_arrow.h>
#include "Animation/settings.h"
#include "Animation/third_person_controller.h"
#include <render/mesh.h>
#include <fstream>
#include <unordered_set>
#include "Physics/collision/ragdoll_provider.h"


SYSTEM(stage=act; require_not=RagdollProvider collision) animation_player_update(
  AnimationPlayer &animationPlayer,
  Settings &settings)
{
  float dt = Time::delta_time();

  if (animationPlayer.playerType == AnimationPlayerType::AnimationPlayer)
  {
    animationPlayer.index.update(dt, settings.lerpTime);
  }
  
  animationPlayer.currentCadr = animationPlayer.index.get_lerped_cadr();
  animationPlayer.rootDeltaTranslation = animationPlayer.currentCadr.rootLinearVelocity;
  animationPlayer.rootDeltaRotation = animationPlayer.currentCadr.rootAngularVelocity;
  animationPlayer.tree.set_cadr(animationPlayer.currentCadr);
  animationPlayer.tree.calculate_bone_transforms();
}

void printNodeTree(int &i, const AnimationTree &tree, const std::string &parent, const AnimationNodeData &data, std::ostream &file, const std::unordered_set<std::string> &ignore = {})
{
  file << i++ << "> " << data.name;
  if(data.parent < tree.nodes.size()) {
    file << "(" << tree.nodes.at(data.parent).get_name() << ")" << std::endl;
    vec3 len = data.translation;
    file << "\tLen = (" << len.x << ", " << len.y << ", " << len.z << ")";
    vec3 pos = tree.nodes.at(data.parent).get_data().translation;
    file << "\tPos = (" << pos.x << ", " << pos.y << ", " << pos.z << ")";
  }
  file << std::endl;
  if(!ignore.contains(data.name)) {
    for (int n: data.childs) {
        printNodeTree(i, tree, data.name, tree.nodes[n].get_data(), file, ignore);
    }
  }
}

EVENT(scene=game, editor) init_animation_character (
  const ecs::OnEntityCreated &,
  AnimationPlayer &animationPlayer)
{
  if (animationPlayer.dataBase)
  {
    animationPlayer.dataBase.load();
    animationPlayer.dataBase->acceleration_structs(true);
    animationPlayer.index = AnimationLerpedIndex(animationPlayer.dataBase, animationPlayer.clip, animationPlayer.frame);
    if (animationPlayer.index)
      animationPlayer.currentCadr = AnimationCadr(animationPlayer.index.get_lerped_cadr());
    animationPlayer.tree = AnimationTree(&animationPlayer.dataBase->tree);
    animationPlayer.motionMatching = 
      MotionMatching(animationPlayer.dataBase, animationPlayer.index);
  }
  else
    return;
  AnimationTree &tree = animationPlayer.tree;
  tree.set_cadr(animationPlayer.currentCadr);
  tree.calculate_bone_transforms();

  std::ofstream file("logs/bones.txt");
  file.precision(4);
  int i = 0;
  printNodeTree(i, tree, "", tree.nodes[0].get_data(), file, {"LeftHand", "RightHand"});
  file.close();

}

SYSTEM(scene=game, editor; stage=act) update_bone_remap(
  AnimationPlayer &animationPlayer,
  const Asset<Mesh> &mesh,
  bool &bone_remaped)
{
  if (!bone_remaped && mesh.loaded())
  {
    const AnimationTree &tree = animationPlayer.tree;
    animationPlayer.treeBoneToMesh.resize(tree.nodes.size());
    for (uint i = 0, n = tree.nodes.size(); i < n && mesh; i++)
    {
      auto it2 = mesh->bonesMap.find(tree.nodes[i].get_name());
      animationPlayer.treeBoneToMesh[i] = 
        (it2 != mesh->bonesMap.end()) ? it2->second : -1;
    }
    bone_remaped = true;
  }
}
EVENT(scene=game) init_animation_material(
  const ecs::OnEntityCreated &,
  Asset<Material> &material)
{
  if (material && !material.is_copy()) {
      material = material.copy();
  }
}