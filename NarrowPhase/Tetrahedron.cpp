#include "Tetrahedron.h"
#include "Triangle.h"

Tetrahedron::Tetrahedron(Vec3 centre, float radius) : ConvexPolyhedron(4, 4)
{
	SetPosition(centre);
	float invRoot3 = radius / sqrt(3.0f);
	localPoints[0] = Vec3(invRoot3, invRoot3, invRoot3);
	localPoints[1] = Vec3(-invRoot3, -invRoot3, invRoot3);
	localPoints[2] = Vec3(-invRoot3, invRoot3, -invRoot3);
	localPoints[3] = Vec3(invRoot3, -invRoot3, -invRoot3);
	int indices[12] = {0, 1, 2, 0, 3, 2, 2, 3, 1, 3, 1, 0};
	InitialiseTris(indices);
	baseBB.InitFromPoints(localPoints, 4);
}

Tetrahedron::~Tetrahedron(void)
{
}
