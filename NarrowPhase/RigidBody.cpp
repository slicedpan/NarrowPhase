#include "RigidBody.h"


RigidBody::RigidBody(void) : 
	position(0, 0, 0), 
	lastPosition(0, 0, 0), 
	acceleration(0, 0, 0), 
	mass(1),
	orientation(1.0, 0.0, 0.0, 0.0),
	angularVelocity(1.0, 0.0, 0.0, 0.0),
	debugColour(1.0, 1.0, 1.0, 1.0)
{
	transform.MakeDiag();
	baseBB.SetMax(Vec3(1, 1, 1));
	baseBB.SetMin(Vec3(-1, -1, -1));
}

RigidBody::~RigidBody(void)
{

}

Mat4& RigidBody::GetTransform()
{
	return transform;
}

void RigidBody::CalculateTransform()
{
	transform = qGetTransform(orientation) * HTrans4(position);
}

void RigidBody::CalculateBB()
{
	currentBB = baseBB.Transform(transform);
}

AABB& RigidBody::GetAABB()
{
	return currentBB;
}


