#include "ParticleSystem.h"
#include "ColouredParticle.h"
#include "PhysicsSystem.h"
#include "ICollidable.h"
#include "Contact.h"
#include "IForceField.h"
#include <cstdlib>
#include <glut.h>

ColouredParticleSystem::ColouredParticleSystem(Vec3 position, Vec3 velocity, Vec3 colour, int particleNum, float creationRate)
{
	this->position = position;
	this->velocity = velocity;
	this->colour = colour;
	this->particleNum = particleNum;
	particleLifetime = (int)((particleNum / creationRate) * 1000);
	particleCounter = 0;
	msTimeBetweenSpawn = (int)(1000.0f / creationRate);
	msCounter = 0;
	particles.reserve(particleNum);
}

ColouredParticleSystem::~ColouredParticleSystem(void)
{
	for (int i = 0; i < particles.size(); ++i)
	{
		delete particles[i];
	}
}

Vec3 ColouredParticleSystem::RandomVector(float maxLength)
{
	float length = rand() / (float)RAND_MAX;
	length *= maxLength;
	Vec3 vec = Vec3(rand() / (float)RAND_MAX - 0.5f, rand() / (float)RAND_MAX - 0.5f, rand() / (float)RAND_MAX - 0.5f);
	norm(vec);
	vec *= length;
	return vec;
}

void ColouredParticleSystem::Update(float msSinceLast)
{
	msCounter += (int)msSinceLast;
	if (msCounter > msTimeBetweenSpawn)
	{
		for (int i = 0; i < (int)(msCounter / msTimeBetweenSpawn); ++i)
		{
			CreateParticle();
		}
		msCounter = 0;		
	}
	for (int i = 0; i < particles.size(); ++i)
	{	
		if (particles[i]->Asleep)
			continue;
		for (int j = 0; j < forces.size(); ++j)
		{
			forces[j]->ApplyForce(particles[i]);
		}
		ICollidable * coll;
		if (coll = PhysicsSystem::GetCurrentInstance()->CollideWith(particles[i]->GetPosition()))
		{
			Contact* contact = coll->GetContact(particles[i]->GetPosition());
			particles[i]->SetPosition(contact->Point);
			particles[i]->SetVelocity(-reflect(particles[i]->GetVelocity(), contact->Normal) * particles[i]->Restitution);
			if (len(particles[i]->GetVelocity()) < 0.01f)
			{
				particles[i]->SetVelocity(Vec3(0.0, 0.0, 0.0));
				particles[i]->Asleep = true;
			}
			particles[i]->ClearForces();
		}
		particles[i]->AddForce(particles[i]->GetVelocity() * -0.1f); //drag/friction
		particles[i]->Update(msSinceLast);
	}
}

void ColouredParticleSystem::CreateParticle()
{
	Vec3 pos = position + RandomVector(0.3f);
	Vec3 vel = velocity + RandomVector(0.1f);
	ColouredParticle* cp;
	if (particles.size() < particleNum)
	{
		cp = new ColouredParticle();		
		particles.push_back(cp);
	}		
	else
	{
		cp = particles[particleCounter];
		++particleCounter;
		if (particleCounter >= particles.size())
			particleCounter = 0;
	}
	cp->Initialise(pos, vel, 1.0f, particleLifetime);
	cp->Colour = colour + RandomVector(1.0f);
}

void ColouredParticleSystem::Draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0f);
	for (int i = 0; i < particles.size(); ++i)
	{
		glBegin(GL_POINTS);
		particles[i]->Draw();
		glEnd();
	}
}
