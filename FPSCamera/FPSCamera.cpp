#include "FPSCamera.h"
#define M_PI 3.14159265

FPSCamera::FPSCamera(void) : Position(0.0f, 0.0f, 0.0f)
{
	Pitch = 0.0f;
	Yaw = 0.0f;	
}

FPSCamera::~FPSCamera(void)
{
}

Mat4 FPSCamera::GetTransform()
{
	Mat4 transform;
	transform.MakeHRot(Vec3(1.0f, 0.0f, 0.0f), Pitch);
	transform *= HRot4(Vec3(0.0f, 1.0f, 0.0f), Yaw);
	transform *= HTrans4(Position);
	return transform;
}

Mat4 FPSCamera::GetViewTransform()
{
	return inv(GetTransform());
}

Vec3 FPSCamera::GetForwardVector()
{
	Vec3 forwardVec;
	forwardVec = proj(Vec4(0.0f, 0.0f, -1.0f, 1.0f) * HRot4(Vec3(1.0f, 0.0f, 0.0f), Pitch) * HRot4(Vec3(0.0f, 1.0f, 0.0f), Yaw));
	return forwardVec;
}

Vec3 FPSCamera::GetRightVector()
{
	Vec3 rightVec;
	rightVec = proj(Vec4(1.0f, 0.0f, 0.0, 1.0f) * HRot4(Vec3(0.0f, 1.0f, 0.0f), Yaw));
	return rightVec;
}

