#include "Box.h"
#include "Contact.h"
#include "Quaternion.h"
#include "Triangle.h"

Box::Box(Vec3 centre, Vec3 extents) : RigidBody(), ConvexPolyhedron(8, 12)
{
	SetPosition(centre);
	this->extents = extents;
	this->max = (extents / 2.0f);
	this->min = -(extents / 2.0f);	
	SetOrientation(Vec4(1.0f, 0.0f, 0.0f, 0.0f));
	baseBB.SetMax(max);
	baseBB.SetMin(min);
	Init();
}

void Box::Init()
{
	Vec3* bbPoints = baseBB.GeneratePoints();
	memcpy(localPoints, bbPoints, sizeof(Vec3) * 8);
	free(bbPoints);
	TriFromQuad(triangles, triangles + 1, 0, 1, 2, 3);
	TriFromQuad(triangles + 2, triangles + 3, 4, 7, 6, 5);
	TriFromQuad(triangles + 4, triangles + 5, 0, 4, 5, 1);
	TriFromQuad(triangles + 6, triangles + 7, 1, 5, 6, 2);
	TriFromQuad(triangles + 8, triangles + 9, 2, 6, 7, 3);
	TriFromQuad(triangles + 10, triangles + 11, 3, 7, 4, 0);
}

Box::~Box(void)
{
	free(points);
	free(triangles);
	free(localPoints);
}

bool Box::PointIntersects(Vec3& point)
{
	if (point[0] > min[0] && point[0] < max[0])
	{
		if (point[1] > min[1] && point[1] < max[1])
		{
			if (point[2] > min[2] && point[2] < max[2])
			{
				return true;
			}
		}
	}
	return false;
}

bool Box::PointWithinDistance(Vec3& point, float dist)
{
	return true; //fix maybe
}

/*

void Box::Draw()
{
	glPushMatrix();		
	glMultMatrixf(transform.Ref());	
	glScalef(extents[0], extents[1], extents[2]);
	glColor(Colour);
	glutSolidCube(1.0);
	glPopMatrix();
}

*/

void Box::Draw()
{
	glPushMatrix();
	glMultMatrixf(GetTransform().Ref());
	glColor(Vec4(1, 1, 1, 1));
	DrawQuad(0, 1, 2, 3);
	DrawQuad(4, 5, 6, 7);
	DrawQuad(0, 1, 5, 4);
	DrawQuad(1, 2, 6, 5);
	DrawQuad(2, 3, 7, 6);
	DrawQuad(3, 0, 4, 7);
	glPopMatrix();
}

void Box::ApplyAngularMomentum(Vec3 axis, float amount)
{
	float s = sin(amount);
	axis.Normalise();
	Vec4 quat = Vec4(cos(amount), s * axis[0], s * axis[1], s * axis[2]);
	ApplyAngularImpulse(quat);
}

Vec3 Box::GetPoint(int index)
{
	return localPoints[index];
}

Vec3 Box::GetTransformedPoint(int index)
{
	return points[index];
}

void Box::Update(float msSinceLast)
{

}

void Box::OnUpdateTransform()
{
	ApplyTransform(GetTransform());
}

void Box::OnNarrowPhase(ConvexPolyhedron* other, Contact contact)
{
	RigidBody::SetDebugColour(Vec4(0, 0.7, 0.7, 1));
}



