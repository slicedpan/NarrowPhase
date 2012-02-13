#pragma once

#include <vector>
#include "Contact.h"

class AABB;
class Vec4;
class RigidBody;
class ConvexPolyhedron;
struct Triangle;

class IDebugDrawer
{
public:
	virtual void DrawAABB(AABB& aabb, Vec4& colour) = 0;
	virtual void DrawRigidBodyMotion(RigidBody& body) = 0;
	virtual void DrawContacts(std::vector<Contact>& contacts) = 0;
	virtual void DrawPoly(ConvexPolyhedron* poly) = 0;
	virtual void DrawTriMesh(Triangle* tri, int triCount, Vec4& colour) = 0;
};


