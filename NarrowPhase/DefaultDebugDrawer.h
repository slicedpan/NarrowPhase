#pragma once

#include "IDebugDrawer.h"


class DefaultDebugDrawer : public IDebugDrawer
{
public:
	DefaultDebugDrawer(void);
	~DefaultDebugDrawer(void);
	void DrawAABB(AABB& aabb, Vec4& colour);
	void DrawRigidBodyMotion(RigidBody& body);
	void DrawContacts(std::vector<Contact>& contacts);
	void DrawPoly(ConvexPolyhedron* poly);
private:
	void DrawContact(Contact& contact);
};

