#include "VoronoiSolver.h"
#include "Triangle.h"
#include "ConvexPolyhedron.h"

VoronoiSolver::VoronoiSolver(void)
{
}

VoronoiSolver::~VoronoiSolver(void)
{
}

bool VoronoiSolver::Check(ConvexPolyhedron* poly1, ConvexPolyhedron* poly2)
{
	Vec3 p1 = poly1->GetCentre();
	Vec3 p2 = poly2->GetCentre();
	Vec3 d = p1 - p2;

	Triangle* tris1 = poly1->GetTriangles();
	Vec3* points2 = poly2->GetPoints();	

	for (int i = 0; i < poly2->GetNumberOfPoints(); ++i)
	{
		Vec3& point = points2[i];
		if (dot(point - p2, d) < 0)
			continue;
		if (minDist < 0.001f)
		{
			lastContact.Normal.Normalise();	//we only need to do this here
			return true;
		}
		for (int j = 0; j < poly1->GetNumberOfTriangles(); ++j)
		{
			Triangle& tri = tris1[j];
			int index = VertexVoronoi(point, tri);

			if (dot(tri.normal, d) > 0)
				continue;

			if (index >= 0)
			{
				float curDist = len(point - tri[index]);
				if (curDist < minDist)
				{
					minDist = curDist;
					lastContact.Point = tri[index];
					lastContact.Normal = point - lastContact.Point;
				}
				continue;	//point is in vertex voronoi region of this triangle
			} 
			index = EdgeVoronoi(point, tri);
			if (index >= 0)
			{
				Vec3 edgePoint;
				Vec3 u = tri[index + 1] - tri[index];
				float l = len(u);
				u.Normalise();
				edgePoint = tri[index] + u * dot(point - tri[index], u);
				float curDist = len(edgePoint - point);
				if (curDist < minDist)
				{
					minDist = curDist;
					lastContact.Point = edgePoint;
					lastContact.Normal = point - edgePoint;
				}
				continue;	//point is in edge voronoi region
			}
			//otherwise we are in face voronoi region
			Vec3 facePoint = point - tri.normal * dot(point - tri[0], tri.normal);
			float curDist = len(facePoint - point);
			if (dot(point - facePoint, tri.normal) < 0)
			{	
				minDist = 0;
				lastContact.Point = facePoint;
				lastContact.Normal = tri.normal;
				break;
			}
			if (curDist < minDist)
			{
				minDist = curDist;
				lastContact.Point = facePoint;
				lastContact.Normal = tri.normal;
			}
		}
	}
	return false;
}

bool VoronoiSolver::Collide(ConvexPolyhedron* poly1, ConvexPolyhedron* poly2)
{
	minDist = FLT_MAX;
	if (Check(poly1, poly2))
		return true;
	lastContact = lastContact.Reverse();
	return Check(poly2, poly1);	
}

int VoronoiSolver::VertexVoronoi(Vec3& point, Triangle& tri)
{
	if (dot((point - tri[0]), (tri[1] - tri[0])) <= 0 && dot(point - tri[0], tri[2] - tri[0]) <= 0)
		return 0;
	if (dot(point - tri[1], tri[2] - tri[1]) <= 0 && dot(point - tri[1], tri[0] - tri[1]) <= 0)
		return 1;
	if (dot(point - tri[2], tri[0] - tri[2]) <= 0 && dot(point - tri[2], tri[1] - tri[2]) <= 0)
		return 2;
	return -1;
}

int VoronoiSolver::EdgeVoronoi(Vec3& point, Triangle& tri)
{
	for (int i = 0; i < 3; ++i)
	{
		if (dot(point - tri[i], tri[i + 1] - tri[i]) < 0 || dot(point - tri[i + 1], tri[i] - tri[i + 1]) < 0)
			continue;
		if (dot(cross(cross(tri[i + 2] - tri[i + 1], tri[i] - tri[i + 1]), tri[i] - tri[i + 1]), point - tri[i + 1]) >= 0)
			return i;
	}
	return -1;
}
