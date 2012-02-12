#pragma once

#include <vector>
#include "Contact.h"
#include "INarrowPhaseSolver.h"

class ConvexPolyhedron;

struct NarrowPhasePair
{
	NarrowPhasePair(ConvexPolyhedron* p1, ConvexPolyhedron* p2)
	{
		this->p1 = p1;
		this->p2 = p2;
	}
	ConvexPolyhedron* p1;
	ConvexPolyhedron* p2;
};

class NarrowPhase
{
public:
	NarrowPhase(void);
	~NarrowPhase(void);
	void CollidePairs(std::vector<NarrowPhasePair>& pairs);
	std::vector<Contact>& GetContacts() { return contacts; }
private:
	std::vector<Contact> contacts;
	INarrowPhaseSolver* solver;
};

