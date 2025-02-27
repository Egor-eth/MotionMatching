#pragma once
#include "serialization/reflection.h"
#include "common.h"
#include "3dmath.h"
#include <vector>
class Transform 
{
private:
REFLECT(
  Transform,
  (vec3) (position),
  (mat4x4) (rotation),
  (vec3) (scale)
)
  mutable mat4 cachedTransform;
  mutable mat3x4 cached3x4Transform;
  mutable bool calculated;
  std::vector<mat4> bones;
public:
  Transform();
  Transform(vec3 position, mat4x4 rotation = mat4x4(1.f), vec3 scale = vec3(1.f));
  Transform(vec3 position, vec3 rotation, vec3 scale = vec3(1.f));
  Transform(const mat4x4 &matrix);
  vec3& get_position();
  const vec3& get_position()const ;
  const mat4x4 &get_transform() const;
  const mat3x4 &get_3x4transform() const;
  mat3 get_rotation() const;
  vec3 get_forward() const;
  vec3 get_right() const;
  vec3 get_up() const;
  vec3 get_scale() const;
  void set_rotation(const mat4& rotation);
  void set_rotation(float yaw = 0, float pitch = 0, float roll = 0);
  void set_rotation(const glm::quat &q);
  void set_position(const vec3 position);
  void set_scale(const vec3 scale);
  void set_from_mat(const mat4 &mat);
  std::vector<mat4>& get_bones()
  {
    return bones;
  }
  const std::vector<mat4>& get_bones() const
  {
    return bones;
  }
};