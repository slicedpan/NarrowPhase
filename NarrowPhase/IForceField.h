#pragma once

class Particle;

class IForceField
{
public:
	virtual void ApplyForce(Particle* particle) = 0;
	virtual void ToggleActive() = 0;
};

