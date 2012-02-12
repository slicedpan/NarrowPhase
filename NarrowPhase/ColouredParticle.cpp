#include "ColouredParticle.h"
#include "glut.h"
#include <svl\SVLgl.h>

ColouredParticle::ColouredParticle() : Particle(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1.0f)
{
	this->Colour = Vec3(1.0f, 1.0f, 1.0f);
	this->alpha = 0.0f;
	this->lifetime = 16.0f;
	this->currentLifetime = lifetime;
	this->Restitution = 0.8f;
	this->Asleep = true;
}

ColouredParticle::~ColouredParticle(void)
{
}

void ColouredParticle::Initialise(Vec3 position, Vec3 velocity, float mass, int lifetime)
{
	this->position = position;
	this->velocity = velocity;
	this->lastPosition = position - velocity;
	this->mass = mass;
	this->lifetime = lifetime;
	this->currentLifetime = lifetime;
	this->alpha = 1.0f;
	this->forceAccumulation.MakeZero();
	this->Asleep = false;
}

void ColouredParticle::Update(float msElapsed)
{
	if (alpha > 0.0f && !Asleep)
	{
		currentLifetime -= msElapsed;
		this->alpha = sqrt((float)currentLifetime / lifetime);
		Particle::Update(msElapsed);
	}
}

void ColouredParticle::Draw()
{
	glColor4f(Colour[0], Colour[1], Colour[2], alpha);
	glVertex(position);
	glColor4f(Colour[0], Colour[1], Colour[2], alpha / 2.0f);
	glVertex(position + (lastPosition - position) * 1.8f);
	glColor4f(Colour[0], Colour[1], Colour[2], alpha / 3.0f);
	glVertex(position + (lastPosition - position) * 3.6f);
}

void ColouredParticle::ReflectForce(Vec3 &normal)
{
	forceAccumulation = reflect(forceAccumulation, normal) * Restitution;
}
