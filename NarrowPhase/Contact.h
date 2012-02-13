#pragma once

#include <svl\SVL.h>

struct Contact
{
	Contact(Vec3& Normal, Vec3& Point)
	{
		this->Normal = Normal;
		this->Point = Point;
	}
	Contact()
	{
		Normal.MakeZero();
		Point.MakeZero();
	}
	Vec3 Normal;
	Vec3 Point;
	Contact Reverse()
	{
		return Contact(-this->Normal, this->Point);
	}
};

