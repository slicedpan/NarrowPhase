#include "CameraController.h"
#include "FPSCamera.h"
#define M_PI 3.14159265

CameraController::CameraController(void)
{
	HasMomentum = false;
	MaxSpeed = 1.0f;
	PitchAngularVelocity = 0.003f;
	YawAngularVelocity = 0.003f;
	camera = 0;
	velocity.MakeZero();
	RestrictToXZPlane = true;
	LinearFriction = 0.25f;
	AngularFriction = 0.25f;
	maxPitch = (90.0f / 89.0f) * (M_PI / 2.0f);
	pitchVel = 0.0f;
	yawVel = 0.0f;
	HasAngularMomentum = false;
}

CameraController::~CameraController(void)
{
}

void CameraController::Update(float msSinceLastUpdate)
{
	float timeFactor = msSinceLastUpdate / 16.0f;

	if (camera != 0)
	{
		if (len(velocity) > 1.0f)
			norm(velocity);

		camera->Position += velocity;
		if (HasMomentum)
		{
			velocity *= (1.0f - LinearFriction);
		}
		else
		{
			velocity.MakeZero();
		}
		rightVec = camera->GetRightVector();
		if (RestrictToXZPlane)
		{
			forwardVec = proj(Vec4(0.0f, 0.0f, -1.0f, 1.0f) * HRot4(Vec3(0.0f, 1.0f, 0.0f), camera->Yaw));
		}
		else
		{
			forwardVec = camera->GetForwardVector();
		}

		camera->Pitch += pitchVel;
		camera->Yaw += yawVel;

		if (camera->Pitch >= maxPitch)
			camera->Pitch = maxPitch;
		else if (camera->Pitch <= -maxPitch)
			camera->Pitch = -maxPitch;

		if (HasAngularMomentum)
		{
			pitchVel *= (1.0f - AngularFriction);
			yawVel *= (1.0f - AngularFriction);
		}
		else
		{
			pitchVel = 0.0f;
			yawVel = 0.0f;
		}
	}	
}

void CameraController::SetCamera(FPSCamera* cam)
{
	camera = cam;
}


#pragma region move camera

void CameraController::MoveBackward()
{
	velocity -= forwardVec * MaxSpeed;
}

void CameraController::MoveForward()
{
	velocity += forwardVec * MaxSpeed;
}

void CameraController::MoveRight()
{
	velocity += rightVec * MaxSpeed;
}

void CameraController::MoveLeft()
{
	velocity -= rightVec * MaxSpeed;
}

void CameraController::MoveUp()
{
	velocity += Vec3(0.0f, 1.0f, 0.0f) * MaxSpeed;
}

void CameraController::MoveDown()
{
	velocity += Vec3(0.0, -1.0f, 0.0f) * MaxSpeed;
}

#pragma endregion

#pragma region rotate camera

void CameraController::ChangePitch(float amount)
{
	pitchVel = amount * PitchAngularVelocity;
}

void CameraController::ChangeYaw(float amount)
{
	yawVel = amount * YawAngularVelocity;
}

#pragma endregion