#include "BruteForceSolver.h"
#include "ConvexPolyhedron.h"


BruteForceSolver::BruteForceSolver(void)
{
}


BruteForceSolver::~BruteForceSolver(void)
{
}

bool BruteForceSolver::Collide(ConvexPolyhedron* p1, ConvexPolyhedron* p2)
{
	for (int i = 0; i < p1->GetNumberOfTriangles(); ++i)
	{
		for (int j = 0; j < p2->GetNumberOfTriangles(); ++j)
		{

		}
	}
	return false;
}

Contact BruteForceSolver::GetContact()
{
	return Contact();
}
