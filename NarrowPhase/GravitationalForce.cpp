#include "GravitationalForce.h"
#include "Particle.h"

GravitationalForce::GravitationalForce(Vec3 direction)
{
	this->direction = direction;
}


GravitationalForce::~GravitationalForce(void)
{
}

void GravitationalForce::ApplyForce(Particle* particle)
{
	if (!active)
		return;
	particle->AddForce(direction * particle->mass);
}
