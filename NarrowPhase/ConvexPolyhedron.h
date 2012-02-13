#pragma once

#include <svl\SVL.h>
#include "Contact.h"

struct Triangle;

class ConvexPolyhedron
{
public:
	ConvexPolyhedron(int numPoints, int numTris);
	~ConvexPolyhedron(void);
	int GetNumberOfTriangles() { return numTris; }
	int GetNumberOfPoints() { return numPoints; }
	Triangle* GetTriangles() { return triangles; }
	Vec3* GetPoints() { return points; }
	Vec3 GetCentre();	
	void ApplyTransform(const Mat4& transform);
	void CalculateNormals();
	virtual void OnNarrowPhase(ConvexPolyhedron* other, Contact contact) {}
	virtual void Init()	{}
	void InitialiseTris(int* indices);
	void SetDebugColour(Vec4& colour) { debugColour = colour; }
	Vec4& GetDebugColour() { return debugColour; }
protected:
	bool centreComputed;
	int numTris;
	int numPoints;
	Triangle* triangles;
	Vec3* localPoints;
	Vec3* points;
	Vec3 centre;
	Vec3 localCentre;
	Vec4 debugColour;
};

