#include "AABB.h"


AABB::AABB(void)
{
}


AABB::~AABB(void)
{
}

AABB AABB::Transform(Mat4& transform)
{
	Vec3 transformedPoint[8];
	Vec3* originalPoints = GeneratePoints();
	Vec3 newMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	Vec3 newMin(FLT_MAX, FLT_MAX, FLT_MAX);
	
	for (int i = 0; i < 8; ++i)
	{
		transformedPoint[i] = proj(Vec4(originalPoints[i], 1) * transform);
		for (int j = 0; j < 3; ++j)
		{
			if (transformedPoint[i][j] > newMax[j])
				newMax[j] = transformedPoint[i][j];
			else if (transformedPoint[i][j] < newMin[j])
				newMin[j] = transformedPoint[i][j];
		}
	}
	free(originalPoints);
	return AABB(newMin, newMax);
}

Vec3* AABB::GeneratePoints()
{
	Vec3* pV = (Vec3*)malloc(sizeof(Vec3) * 8);
	
	pV[0] = max;
	pV[1] = Vec3(max[0], max[1], min[2]);
	pV[2] = Vec3(min[0], max[1], min[2]);
	pV[3] = Vec3(min[0], max[1], max[2]);
	pV[4] = Vec3(max[0], min[1], max[2]);
	pV[5] = Vec3(max[0], min[1], min[2]);
	pV[6] = min;
	pV[7] = Vec3(min[0], min[1], max[2]);

	return pV;
}
