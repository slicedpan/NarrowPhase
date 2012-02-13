#include "BruteForceSolver.h"
#include "ConvexPolyhedron.h"
#include "Triangle.h"

BruteForceSolver::BruteForceSolver(void)
{
}

BruteForceSolver::~BruteForceSolver(void)
{
}

bool BruteForceSolver::Collide(ConvexPolyhedron* p1, ConvexPolyhedron* p2)
{
	ConvexPolyhedron* smallPoly;
	ConvexPolyhedron* largePoly;
	if (p1->GetNumberOfPoints() < p2->GetNumberOfPoints())
	{
		largePoly = p2;
		smallPoly = p1;
	}
	else
	{
		largePoly = p1;
		smallPoly = p2;
	}

	Vec3 d = smallPoly->GetCentre() - largePoly->GetCentre();
	lastContact.Normal = d;
	lastContact.Point = largePoly->GetCentre();

	//Triangle* largeTris = largePoly->GetTriangles();
	Triangle* smallTris = smallPoly->GetTriangles();
	Vec3* largePoints = largePoly->GetPoints();

	/*
	for (int i = 0; i < largePoly->GetNumberOfTriangles(); ++i)
	{		
		if (dot(largeTris[i].normal, d) < 0)
			largeTris[i].debugColour = Vec3(1, 0, 0);
	}
	for (int j = 0; j < smallPoly->GetNumberOfTriangles(); ++j)
	{
		if (dot(smallTris[j].normal, d) > 0)
			smallTris[j].debugColour = Vec3(1, 0, 0);
	}
	*/

	for (int i = 0; i < largePoly->GetNumberOfPoints(); ++i)
	{
		for (int j = 0; j < smallPoly->GetNumberOfTriangles(); ++j)
		{
			
		}
	}
	return true;
}

bool BruteForceSolver::Intersects(Vec3& point, Triangle& tri)
{
	return false;
}

