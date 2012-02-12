#pragma once

#include "IForceField.h"
#include <svl\SVL.h>

class GravitationalForce : public IForceField
{
public:
	GravitationalForce(Vec3 direction);
	~GravitationalForce(void);
	void ApplyForce(Particle* particle);
	inline void ToggleActive()
	{
		active = !active;
	}
private:
	bool active;
	Vec3 direction;
};

