#include "DefaultDebugDrawer.h"
#include "AABB.h"
#include "RigidBody.h"
#include "ConvexPolyhedron.h"
#include "Triangle.h"
#include <svl\SVL.h>
#include <glut.h>
#include <svl\SVLgl.h>

DefaultDebugDrawer::DefaultDebugDrawer(void)
{
}


DefaultDebugDrawer::~DefaultDebugDrawer(void)
{
}

void DefaultDebugDrawer::DrawAABB(AABB& aabb, Vec4& colour)
{
	Vec3* points = aabb.GeneratePoints();
 	glColor(colour);

	glBegin(GL_LINE_STRIP);
	glVertex(points[0]);
	glVertex(points[1]);
	glVertex(points[2]);
	glVertex(points[3]);
	glVertex(points[0]);
	glVertex(points[4]);
	glVertex(points[5]);
	glVertex(points[6]);
	glVertex(points[7]);
	glVertex(points[4]);
	glEnd();

	glBegin(GL_LINES);
	glVertex(points[1]);
	glVertex(points[5]);
	glVertex(points[2]);
	glVertex(points[6]);
	glVertex(points[3]);
	glVertex(points[7]);
	glEnd();

	free(points);
}

void DefaultDebugDrawer::DrawRigidBodyMotion(RigidBody& body)
{
	glColor3f(1, 0, 0);
	Vec3 vel = body.GetVelocity() * 60.0; //approx how far it travels in one sec	
	glBegin(GL_LINES);
	glVertex(body.GetPosition() - vel);
	glVertex(body.GetPosition());
	glEnd();
}

void DefaultDebugDrawer::DrawContacts(std::vector<Contact>& contacts)
{
	for (int i = 0; i < contacts.size(); ++i)
	{
		DrawContact(contacts[i]);
	}
}

void DefaultDebugDrawer::DrawContact(Contact& contact)
{
	Vec3 v1 = contact.Normal + Vec3(1.0, 1.0, 1.0);
	v1 = norm(cross(v1, contact.Normal));
	Vec3 end = contact.Point + contact.Normal;
	glColor3f(0, 1, 0);		
	glPointSize(3.0f);
	glBegin(GL_POINTS);
	glVertex(contact.Point);
	glEnd();
	glBegin(GL_LINES);
	glVertex(contact.Point);
	glVertex(end);
	glVertex(end);
	glVertex(contact.Point + (contact.Normal * 0.8) + (v1 * 0.4));
	glVertex(end);
	glVertex(contact.Point + (contact.Normal * 0.8) - (v1 * 0.4));		
	glEnd();
}

void DefaultDebugDrawer::DrawPoly(ConvexPolyhedron* poly)
{
	Triangle* tris = poly->GetTriangles();
	Vec3* points = poly->GetPoints();
	poly->CalculateNormals();
	glColor3f(0.5, 1, 0);
	glPointSize(3.0f);
	for (int i = 0; i < poly->GetNumberOfTriangles(); ++i)
	{
		Vec3& p1 = points[tris[i].point[0]];
		Vec3& p2 = points[tris[i].point[1]];
		Vec3& p3 = points[tris[i].point[2]];
		glBegin(GL_POINTS);
		glVertex(p1);
		glVertex(p2);
		glVertex(p3);
		glEnd();
		glBegin(GL_LINE_STRIP);
		glVertex(p1);
		glVertex(p2);
		glVertex(p3);
		glVertex(p1);
		glEnd();
		Contact contact(tris[i].normal, (p1 + p2 + p3) / 3);
		DrawContact(contact);
	}
}

