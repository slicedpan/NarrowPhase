#include "CentralForce.h"
#include "Particle.h"

CentralForce::CentralForce(Vec3 centre, float strength)
{
	this->centre = centre;
	this->strength = strength;
}

CentralForce::~CentralForce(void)
{
}

void CentralForce::ApplyForce(Particle* particle)
{
	if (!active)
		return;
	particle->AddForce((centre - particle->GetPosition()) * strength);
}
