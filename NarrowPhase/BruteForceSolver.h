#pragma once

#include "INarrowPhaseSolver.h"

class BruteForceSolver : public INarrowPhaseSolver
{
public:
	BruteForceSolver(void);
	~BruteForceSolver(void);
	bool Collide(ConvexPolyhedron* p1, ConvexPolyhedron* p2);
	Contact GetContact();
};

