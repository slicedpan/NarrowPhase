#include "PhysicsSystem.h"
#include "ICollidable.h"
#include "Contact.h"
#include "RigidBody.h"
#include "IDebugDrawer.h"
#include "ConvexPolyhedron.h"

PhysicsSystem * PhysicsSystem::currentInstance;

PhysicsSystem::PhysicsSystem(void) : debugDrawer(0)
{
}

PhysicsSystem::~PhysicsSystem(void)
{
}

void PhysicsSystem::DrawDebug()
{
	if (!debugDrawer)
		return;
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		debugDrawer->DrawAABB(rigidBodies[i]->GetAABB(), rigidBodies[i]->GetDebugColour());		
		//debugDrawer->DrawRigidBodyMotion(*rigidBodies[i]);
		ConvexPolyhedron* poly = rigidBodies[i]->GetPoly();
		if (poly)
		{
			//debugDrawer->DrawPoly(poly);
			debugDrawer->DrawTriMesh(poly->GetTriangles(), poly->GetNumberOfTriangles(), poly->GetDebugColour());
		}
	}

	debugDrawer->DrawContacts(narrowPhase.GetContacts());
}

void PhysicsSystem::AddCollidable(ICollidable* obj)
{
	collidables.push_back(obj);
}

ICollidable* PhysicsSystem::CollideWith(Vec3 point)
{
	for (int i = 0; i < collidables.size(); ++i)
	{
		if (collidables[i]->PointIntersects(point))
			return collidables[i];
	}
	return 0;
}

void PhysicsSystem::Integrate(float timeStep)
{
	float timeSquared = timeStep * timeStep;
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		rigidBodies[i]->SetDebugColour(Vec4(1, 1, 1, 1));
		rigidBodies[i]->SetPosition((2 * rigidBodies[i]->GetPosition()) - rigidBodies[i]->GetLastPosition() + rigidBodies[i]->GetAcceleration() * timeSquared);
		rigidBodies[i]->SetOrientation(qMultiply(rigidBodies[i]->GetOrientation(), rigidBodies[i]->GetAngularVelocity()));
		rigidBodies[i]->CalculateTransform();
		rigidBodies[i]->CalculateBB();
		rigidBodies[i]->OnUpdateTransform();
	}	
	broadPhase.GenerateCollisions();
	std::vector<BroadPhasePair>& pairs = broadPhase.GetPairs();
	std::vector<NarrowPhasePair> nPairs;
	for (int i = 0; i < pairs.size(); ++i)
	{
		if (pairs[i].p1->OnBroadPhaseCollide(pairs[i].p2) && pairs[i].p2->OnBroadPhaseCollide(pairs[i].p1))
		{
			ConvexPolyhedron* poly1 = pairs[i].p1->GetPoly();
			ConvexPolyhedron* poly2 = pairs[i].p2->GetPoly();
			if (poly1 && poly2)
				nPairs.push_back(NarrowPhasePair(poly1, poly2));
		}
	}
	narrowPhase.CollidePairs(nPairs);
}

void PhysicsSystem::AddRigidBody(RigidBody* bodyToAdd)
{
	rigidBodies.push_back(bodyToAdd);
	broadPhase.AddBody(bodyToAdd);
}

void PhysicsSystem::SetDebugDrawer(IDebugDrawer* debugDrawer)
{
	this->debugDrawer = debugDrawer;
}

