#pragma once

#include "svl/svl.h"

class FPSCamera
{
public:
	FPSCamera(void);
	~FPSCamera(void);
	Mat4 GetTransform();
	Mat4 GetViewTransform();
	float Pitch, Yaw;
	Vec3 Position;
	Vec3 GetForwardVector();
	Vec3 GetRightVector();
};

