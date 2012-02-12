#include "ConvexPolyhedron.h"
#include "Triangle.h"

ConvexPolyhedron::ConvexPolyhedron(int numPoints, int numTris)
{
	triangleNum = numTris;
	points = (Vec3*)malloc(sizeof(Vec3) * numPoints);
	localPoints = (Vec3*)malloc(sizeof(Vec3) * numPoints);
	triangles = (Triangle*)malloc(sizeof(Triangle) * numTris);	
}


ConvexPolyhedron::~ConvexPolyhedron(void)
{
	free(localPoints);
	free(points);
	free(triangles);
}

void ConvexPolyhedron::CalculateNormals()
{
	for (int i = 0; i < triangleNum; ++i)
	{
		triangles[i].SetNormal(points[triangles[i].point[0]], points[triangles[i].point[1]], points[triangles[i].point[2]]);
	}
}

void ConvexPolyhedron::ApplyTransform(const Mat4& transform)
{
	for (int i = 0; i < 8; ++i)
	{
		points[i] = proj(Vec4(localPoints[i], 1) * transform);
	}
}