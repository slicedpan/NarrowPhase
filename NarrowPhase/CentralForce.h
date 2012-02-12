#pragma once
#include "iforcefield.h"
#include <svl\SVL.h>

class CentralForce : public IForceField
{
public:
	CentralForce(Vec3 centre, float strength);
	~CentralForce(void);
	void ApplyForce(Particle* particle);
	inline void ToggleActive()
	{
		active = !active;
	}
private:
	bool active;
	Vec3 centre;
	float strength;
};

