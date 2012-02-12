#include "NarrowPhase.h"
#include "PhysicsSystem.h"
#include "BruteForceSolver.h"

NarrowPhase::NarrowPhase(void)
{
	solver = new BruteForceSolver();
}

NarrowPhase::~NarrowPhase(void)
{
}

void NarrowPhase::CollidePairs(std::vector<NarrowPhasePair>& pairs)
{
	contacts.clear();
	/*if (pairs.size() == 0)
		return;*/
	for (int i = 0; i < pairs.size(); ++i)
	{
		if (solver->Collide(pairs[i].p1, pairs[i].p2))
			contacts.push_back(solver->GetContact());
	}
	contacts.push_back(Contact(Vec3(0, 1, 0), Vec3(0, 1, 0)));
}
