//
// Created by egor on 26.02.23.
//

#include "debug_drawer.h"
#include "common.h"
DebugDrawer::DebugDrawer()
{

}

DebugDrawer::~DebugDrawer()
{

}

void DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{

}

void   DebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{

}

void   DebugDrawer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{

}

void   DebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
{

}

void   DebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void   DebugDrawer::reportErrorWarning(const char* warningString)
{
  debug_error(warningString);
}

void   DebugDrawer::draw3dText(const btVector3& location, const char* textString)
{

}