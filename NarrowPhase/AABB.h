#pragma once

#include <svl\SVL.h>

class AABB
{
public:
	AABB(void);	
	inline AABB(Vec3& minPoint, Vec3& maxPoint)
	{
		SetMin(minPoint);
		SetMax(maxPoint);
		CalcCentre();
	}			
	~AABB(void);
	inline Vec3 GetMin()
	{
		return min;
	}
	inline Vec3 GetMax()
	{
		return max;
	}
	inline bool Intersects(Vec3& point)
	{
		return point[0] > min[0] && point[0] < max[0] && point[1] > min[1] && point[1] < max[1] && point[2] > min[2] && point[2] < max[2];
	}
	inline void SetMax(Vec3& point)
	{
		max = point;
		CalcCentre();
	}
	inline void SetMin(Vec3& point)
	{
		min = point;
		CalcCentre();
	}
	AABB Transform(Mat4& transform);
	Vec3* GeneratePoints();
private:
	Vec3 min;
	Vec3 max;	
	Vec3 centre;
	inline void CalcCentre()
	{
		centre = (GetMax() - GetMin()) / 2.0;
	}
};

