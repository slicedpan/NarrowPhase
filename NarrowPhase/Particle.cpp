#include "Particle.h"

Particle::Particle(Vec3 position, Vec3 velocity, float mass)
{
	this->position = position;
	this->lastPosition = position - velocity;
	this->velocity = velocity;
	this->mass = mass;
	this->forceAccumulation.MakeZero();
}

Particle::~Particle(void)
{
}

void Particle::AddForce(Vec3 forceVector)
{
	forceAccumulation += forceVector;
}

void Particle::Update(float msElapsed)
{
	Vec3 tmp = position;
	position = (2 * position - lastPosition) + (forceAccumulation / mass) * 0.000256f;
	lastPosition = tmp;
	velocity = position - tmp;
	ClearForces();
}
