#pragma once

#include "Particle.h"

class ColouredParticle : public Particle
{
public:
	ColouredParticle();
	~ColouredParticle(void);
	void Update(float msElapsed);
	Vec3 Colour;
	void Initialise(Vec3 position, Vec3 velocity, float mass, int lifetime);
	inline bool IsRecyclable()
	{
		return (alpha >= 0.0f);
	}
	void Draw();
	void ReflectForce(Vec3 &normal);
	float Restitution;
	inline void SetVelocity(Vec3 &vel)
	{
		velocity = vel;
		lastPosition = position - vel;
	}
	inline Vec3& GetVelocity()
	{
		return velocity;
	}
	bool Asleep;
private:
	float alpha;
	int lifetime;
	int currentLifetime;
};

