
#include "debug_drawer.h"
#include "common.h"
#include "bulletutil.h"
#include <render/debug_arrow.h>

DebugDrawer::DebugDrawer()
{

}

DebugDrawer::~DebugDrawer()
{

}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
  draw_arrow(bt2glm(from), bt2glm(to), bt2glm(fromColor), 0.05f, true);
}

void   DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
  draw_arrow(bt2glm(from), bt2glm(to), bt2glm(color), 0.05f, true);
}

void   DebugDrawer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{

}

void   DebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
{
  drawLine(a, b, color);
  drawLine(b, c, color);
  drawLine(c, a, color);
}

void   DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
  drawLine(PointOnB, normalOnB * distance, color);
  debug_log("contact");
}

void   DebugDrawer::reportErrorWarning(const char* warningString)
{
  debug_error(warningString);
}

void   DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}