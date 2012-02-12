#pragma once

#include "svl/svl.h"

class FPSCamera;

class CameraController
{
public:
	CameraController();
	~CameraController();
	float MaxSpeed;
	float PitchAngularVelocity;
	float YawAngularVelocity;
	bool HasMomentum;
	bool HasAngularMomentum;
	float LinearFriction;
	float AngularFriction;
	void Update(float msSinceLastUpdate);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void MoveForward();
	void MoveBackward();
	void ChangeYaw(float amount);
	void ChangePitch(float amount);
	bool RestrictToXZPlane;
	void SetCamera(FPSCamera* camera);
private:
	Vec3 velocity;
	Vec3 forwardVec;
	Vec3 rightVec;
	FPSCamera * camera;
	float pitchVel;
	float yawVel;
	float maxPitch;
};

