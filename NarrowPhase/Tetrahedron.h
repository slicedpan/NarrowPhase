#pragma once

#include "RigidBody.h"
#include "ConvexPolyhedron.h"

class Tetrahedron : public RigidBody, public ConvexPolyhedron
{
public:
	Tetrahedron(Vec3 centre, float radius);
	~Tetrahedron(void);
	bool OnBroadPhaseCollide(RigidBody* other) { return true; }
	void OnNarrowPhase(ConvexPolyhedron* other, Contact contact) { RigidBody::SetDebugColour(Vec4(0, 0.7, 0.7, 1)); }
	ConvexPolyhedron* GetPoly() { return this; }
	void OnUpdateTransform() { ApplyTransform(GetTransform()); }
};

