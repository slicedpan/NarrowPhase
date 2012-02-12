#pragma once

#include "svl/svl.h"
#include "ICollidable.h"

class Plane : public ICollidable
{
public:
	Plane(Vec3 normal, Vec3 position);
	~Plane(void);
	inline float GetDistanceTo(Vec3 point)
	{
		point -= position;
		return dot(point, normal);
	}
	void Draw();
	inline Vec3 GetNormal()
	{
		return normal;
	}
	inline bool PointIntersects(Vec3& point)
	{	
		return (GetDistanceTo(point) < 0.0);
	}
	inline bool PointWithinDistance(Vec3& point, float dist)
	{
		return (fabs(GetDistanceTo(point)) < dist);
	}
	Vec3 GetRestoringForce(Vec3 point);
	Contact * GetContact(Vec3& point);
private:
	Vec3 normal;
	Vec3 position;
	Vec3 v1, v2;
};

