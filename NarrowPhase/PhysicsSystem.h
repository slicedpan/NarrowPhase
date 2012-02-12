#pragma once

#include <vector>
#include <svl\SVL.h>
#include "BroadPhase.h"
#include "NarrowPhase.h"

class ICollidable;
class RigidBody;
struct Contact;
class IDebugDrawer;
class ConvexPolyhedron;

class PhysicsSystem
{
public:
	~PhysicsSystem(void);
	inline static PhysicsSystem* GetCurrentInstance()
	{
		if (currentInstance == 0)
			currentInstance = new PhysicsSystem();
		return currentInstance;
	}
	void AddCollidable(ICollidable* obj);
	void AddRigidBody(RigidBody* bodyToAdd);
	void Integrate(float timeStep);
	ICollidable* CollideWith(Vec3 point);
	void DrawDebug();
	void SetDebugDrawer(IDebugDrawer* debugDrawer);
	inline IDebugDrawer* GetDebugDrawer() {return debugDrawer;};
private:
	static PhysicsSystem * currentInstance;
	IDebugDrawer*  debugDrawer;
	std::vector<ICollidable*> collidables;
	std::vector<RigidBody*> rigidBodies;
	PhysicsSystem(void);
	BroadPhase broadPhase;
	NarrowPhase narrowPhase;
};

