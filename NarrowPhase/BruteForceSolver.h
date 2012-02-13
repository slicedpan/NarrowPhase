#pragma once

#include "INarrowPhaseSolver.h"

struct Triangle;

class BruteForceSolver : public INarrowPhaseSolver
{
public:
	BruteForceSolver(void);
	~BruteForceSolver(void);
	bool Collide(ConvexPolyhedron* p1, ConvexPolyhedron* p2);
	Contact& GetContact() { return lastContact; }
private:
	bool Intersects(Vec3& point, Triangle& tri);
	Contact lastContact;
};

