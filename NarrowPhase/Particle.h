#pragma once

#include "svl/svl.h"

class Particle
{
public:
	Particle(Vec3 position, Vec3 velocity, float mass);
	~Particle(void);
	void AddForce(Vec3 forceVector);
	inline Vec3 GetVelocity()
	{
		return velocity;
	}
	virtual void Update(float msElapsed);
	inline Vec3 GetPosition()
	{
		return position;
	}
	inline void SetPosition(const Vec3 &p)
	{
		position = p;
	}
	inline void ClearForces()
	{
		forceAccumulation.MakeZero();
	}
	float mass;
protected:
	Vec3 position;
	Vec3 lastPosition;
	Vec3 velocity;
	Vec3 forceAccumulation;
};

