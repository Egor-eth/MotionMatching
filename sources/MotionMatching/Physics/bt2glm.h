#pragma once
#include <3dmath.h>
#include <bullet/btBulletDynamicsCommon.h>

inline vec3 bt2glm(const btVector3 &v)
{
  return {v.x(), v.y(), v.z()};
}

inline btVector3 glm2bt(const vec3 &v)
{
  return {v.x, v.y, v.z};
}

inline mat3 bt2glm(const btMatrix3x3 &m)
{
  return {m[0][0], m[0][1], m[0][2],
          m[1][0], m[1][1], m[1][2],
          m[2][0], m[2][1], m[2][2]};
}

inline btMatrix3x3 glm2bt(const mat3 &m)
{
  return {m[0][0], m[0][1], m[0][2],
          m[1][0], m[1][1], m[1][2],
          m[2][0], m[2][1], m[2][2]};
}