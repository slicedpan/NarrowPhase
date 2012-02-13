#include "RigidBody.h"
#include "Contact.h"

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

void RigidBody::ApplyContact(Contact& contact)
{
	Vec3 vel = dot(contact.Normal, velocity) * contact.Normal;
	ApplyImpulse(-2 * vel);
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

void RigidBody::ApplyAngularImpulse(Vec3& axis, float amount)
{
	float s = sin(amount);
	axis.Normalise();
	Vec4 quat = Vec4(cos(amount), s * axis[0], s * axis[1], s * axis[2]);
	ApplyAngularImpulse(quat);
}


