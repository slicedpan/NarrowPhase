#pragma once

#include <svl\SVL.h>
#include "Contact.h"

struct Triangle;

class ConvexPolyhedron
{
public:
	ConvexPolyhedron(int numPoints, int numTris);
	~ConvexPolyhedron(void);
	int GetNumberOfTriangles() { return triangleNum; }
	Triangle* GetTriangles() { return triangles; }
	Vec3* GetPoints() { return points; }
	void ApplyTransform(const Mat4& transform);
	void CalculateNormals();
	virtual void OnNarrowPhase(ConvexPolyhedron* other, Contact contact) {}
	virtual void Init() 
	{

	}
protected:
	int triangleNum;
	Triangle* triangles;
	Vec3* localPoints;
	Vec3* points;
};

