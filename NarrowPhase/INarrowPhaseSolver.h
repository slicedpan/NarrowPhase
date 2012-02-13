#pragma once

#include "Contact.h"

class ConvexPolyhedron;

class INarrowPhaseSolver
{
public:
	virtual bool Collide(ConvexPolyhedron* p1, ConvexPolyhedron* p2) = 0;
	virtual Contact& GetContact() = 0;
};

