#pragma once

#include "svl/svl.h"

struct Contact;

class ICollidable
{
public:
	virtual bool PointIntersects(Vec3& point) = 0;
	virtual bool PointWithinDistance(Vec3& point, float dist) = 0;	
	virtual Contact* GetContact(Vec3& point) = 0;
};

