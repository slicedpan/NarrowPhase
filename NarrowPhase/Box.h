#pragma once
#include "RigidBody.h"
#include <glut.h>
#include <svl\SVLgl.h>
#include "ConvexPolyhedron.h"

class Box : public RigidBody, public ConvexPolyhedron
{
public:
	Box(Vec3 centre, Vec3 extents);
	~Box(void);
	bool PointIntersects(Vec3& point);
	bool PointWithinDistance(Vec3& point, float dist);
	void Draw();
	Vec3 GetPoint(int index);
	Vec3 GetTransformedPoint(int index);
	void ApplyAngularMomentum(Vec3 axis, float amount);
	void Update(float msSinceLast);
	void Init();
	void OnUpdateTransform();
	void OnNarrowPhase(ConvexPolyhedron* other, Contact contact);
	ConvexPolyhedron* GetPoly() { return this; }
	bool OnBroadPhaseCollide(RigidBody* other) { return true; }
private:
	inline void DrawQuad(int i0, int i1, int i2, int i3)
	{
		glBegin(GL_QUADS);
		glVertex(localPoints[i0]);
		glNormal(localPoints[i0]);
		glVertex(localPoints[i1]);
		glNormal(localPoints[i1]);
		glVertex(localPoints[i2]);
		glNormal(localPoints[i2]);
		glVertex(localPoints[i3]);
		glNormal(localPoints[i3]);
		glEnd();
	}	
	Vec3 extents;
	Vec3 max;
	Vec3 min;
};



