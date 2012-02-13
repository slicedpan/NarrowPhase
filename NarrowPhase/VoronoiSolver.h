#pragma once

#include "INarrowPhaseSolver.h"
#include "Contact.h"

class ConvexPolyhedron;
struct Triangle;

class VoronoiSolver : public INarrowPhaseSolver
{
public:
	VoronoiSolver(void);
	~VoronoiSolver(void);
	bool Collide(ConvexPolyhedron* poly1, ConvexPolyhedron* poly2);	
	Contact& GetContact() { return lastContact; }
private:
	Contact lastContact;
	bool Check(ConvexPolyhedron* poly1, ConvexPolyhedron* poly2);
	int VertexVoronoi(Vec3& point, Triangle& tri);
	int EdgeVoronoi(Vec3& point, Triangle& tri);
	float minDist;
};

