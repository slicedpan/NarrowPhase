#pragma once

#include <vector>
#include <svl\SVL.h>

class ColouredParticle;
class IForceField;

class ColouredParticleSystem
{
public:
	ColouredParticleSystem(Vec3 position, Vec3 velocity, Vec3 colour, int particleNum, float creationRate);
	~ColouredParticleSystem(void);
	void Update(float msSinceLast);
	void Draw();
	inline void AddForce(IForceField* force)
	{
		forces.push_back(force);
	}
	inline int GetParticleNum()
	{
		return particles.size();
	}
	static Vec3 RandomVector(float maxLength);
private:
	std::vector<ColouredParticle*> particles;
	std::vector<IForceField*> forces;
	Vec3 position, velocity, colour;
	int particleNum;
	int msCounter;
	float msTimeBetweenSpawn;
	void CreateParticle();	
	int particleLifetime;
	int particleCounter;
};

