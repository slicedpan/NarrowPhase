#pragma once

#include <svl\SVL.h>

struct Triangle
{
	Triangle(int p1, int p2, int p3) : pointArray(0), debugColour(0, 1, 0)
	{
		point[0] = p1;
		point[1] = p2;
		point[2] = p3;
	}
	Triangle() : pointArray(0), debugColour(0, 1, 0)
	{
		point[0] = 0;
		point[1] = 0;
		point[2] = 0;
	}
	void SetNormal(Vec3 normal)
	{
		this->normal = normal;
	}
	void SetNormal(Vec3 p1, Vec3 p2, Vec3 p3)
	{
		Vec3 u = p2 - p1;
		Vec3 v = p3 - p1;
		normal = norm(cross(u, v));
	}
	int point[3];
	Vec3 normal;
	Vec3* pointArray;
	Vec3& operator[] (int index)
	{
		return *(pointArray + point[index % 3]);
	}
	Vec3 debugColour;
};

inline void TriFromQuad(Triangle* t1, Triangle* t2, int q1, int q2, int q3, int q4)
{
	t1->point[0] = q1;
	t1->point[1] = q2;
	t1->point[2] = q3;

	t2->point[0] = q1;
	t2->point[1] = q3;
	t2->point[2] = q4;
}

