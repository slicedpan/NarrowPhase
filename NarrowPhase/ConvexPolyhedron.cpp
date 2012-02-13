#include "ConvexPolyhedron.h"
#include "Triangle.h"

ConvexPolyhedron::ConvexPolyhedron(int numPoints, int numTris)
	: centreComputed(false),
	centre(0, 0, 0),
	localCentre(0, 0, 0),
	debugColour(0.5, 0.5, 0.5, 1)
{
	this->numTris = numTris;
	this->numPoints = numPoints;
	points = (Vec3*)malloc(sizeof(Vec3) * numPoints);
	localPoints = (Vec3*)malloc(sizeof(Vec3) * numPoints);
	triangles = (Triangle*)malloc(sizeof(Triangle) * numTris);
	for (int i = 0; i < numTris; ++i)
	{
		triangles[i].pointArray = points;
	}
}

Vec3 ConvexPolyhedron::GetCentre()
{ 
	if (centreComputed)
		return centre;	
	
	for (int i = 0; i < numPoints; ++i)
	{
		localCentre += localPoints[i];
	}
	localCentre /= numPoints;
	for (int i = 0; i < numPoints; ++i)
	{
		centre += points[i];
	}
	centre /= numPoints;
	centreComputed = true;
	return centre;	
}

ConvexPolyhedron::~ConvexPolyhedron(void)
{
	free(localPoints);
	free(points);
	free(triangles);
}

void ConvexPolyhedron::CalculateNormals()
{
	for (int i = 0; i < numTris; ++i)
	{
		triangles[i].SetNormal(points[triangles[i].point[0]], points[triangles[i].point[1]], points[triangles[i].point[2]]);
		triangles[i].debugColour = Vec3(0, 1, 0);
	}
}

void ConvexPolyhedron::ApplyTransform(const Mat4& transform)
{
	for (int i = 0; i < numPoints; ++i)
	{
		points[i] = proj(Vec4(localPoints[i], 1) * transform);
	}
	CalculateNormals();
	centre = proj(Vec4(localCentre, 1) * transform);
}

void ConvexPolyhedron::InitialiseTris(int* indices)
{
	int count = 0;
	for (int i = 0; i < numTris; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			triangles[i].point[count % 3] = indices[count];
			++count;
		}
	}
}