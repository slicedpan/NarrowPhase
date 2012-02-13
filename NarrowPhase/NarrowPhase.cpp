#include "NarrowPhase.h"
#include "PhysicsSystem.h"
#include "VoronoiSolver.h"
#include "ConvexPolyhedron.h"

NarrowPhase::NarrowPhase(void)
{
	solver = new VoronoiSolver();
}

NarrowPhase::~NarrowPhase(void)
{
}

void NarrowPhase::CollidePairs(std::vector<NarrowPhasePair>& pairs)
{
	contacts.clear();
	if (pairs.size() == 0)
		return;
	for (int i = 0; i < pairs.size(); ++i)
	{
		Contact& contact = solver->GetContact();
		contacts.push_back(contact);

		if (solver->Collide(pairs[i].p1, pairs[i].p2))
		{			
			pairs[i].p1->OnNarrowPhase(pairs[i].p2, contact.Reverse());
			pairs[i].p2->OnNarrowPhase(pairs[i].p1, contact);
		}

	}
}
