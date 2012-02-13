// Skeleton program for GLUT applications.

// Link with: opengl32.lib, glu32.lib, glut32.lib.

#include <math.h>
#include <iostream>
#include <strstream>
#include <iomanip>
#include <glut.h>
#include "../FPSCamera/FPSCamera.h"
#include "../FPSCamera/CameraController.h"
#include "Plane.h"
#include "ParticleSystem.h"
#include "PhysicsSystem.h"
#include "GravitationalForce.h"
#include "CentralForce.h"
#include "Box.h"
#include "DefaultDebugDrawer.h"
#include "Tetrahedron.h"

using namespace std;

// Initial size of graphics window.
const int WIDTH  = 1200;
const int HEIGHT = 800;

// Current size of window.
int width  = WIDTH;
int height = HEIGHT;

float xMouse = (float)width / 2.0f;
float yMouse = (float)height / 2.0f;

float dMouseX = 0.0f;
float dMouseY = 0.0f;

bool keystate[256];
bool lastKeystate[256];

// Bounds of viewing frustum.
double nearPlane =  0.1f;
double farPlane  = 1000.0f;

// Viewing angle.
double fovy = 40.0;

// Variables.
double alpha = 0;                                  // Set by idle function.
double beta = 0;                                   // Set by mouse X.
double dist = - (farPlane - nearPlane) / 2;    // Set by mouse Y.

CameraController* cameraController;
FPSCamera* camera;

int fps = 60;
bool physicsActive = true;

Plane * groundPlane;
ColouredParticleSystem* particleSystem;

Vec3 maxPos(25, 30, 25);
Vec3 minPos(-25, 10, -25);

AABB bounds(minPos, maxPos);

Box* testBox;

std::vector<Box*> boxes;
int numBoxes = 2;
Vec3 testVel;

// This function is called to display the scene.

void AddBox()
{
	Box* box = new Box(ColouredParticleSystem::RandomVector(30.0) + Vec3(0, 15, 0), ColouredParticleSystem::RandomVector(10.0) + Vec3(5, 5, 5));
	box->ApplyImpulse(ColouredParticleSystem::RandomVector(0.05));
	box->ApplyAngularMomentum(ColouredParticleSystem::RandomVector(1), ((float)rand() * 0.01) / RAND_MAX);
	box->ConvexPolyhedron::SetDebugColour(Vec4(ColouredParticleSystem::RandomVector(1), 1));
	boxes.push_back(box);
	PhysicsSystem::GetCurrentInstance()->AddRigidBody(box);
}

void AddTetra()
{
	Tetrahedron* tetra = new Tetrahedron(ColouredParticleSystem::RandomVector(30.0) + Vec3(0, 15, 0), (float)rand() * 10.0f / RAND_MAX);
	tetra->ApplyImpulse(ColouredParticleSystem::RandomVector(0.05));
	tetra->ApplyAngularImpulse(ColouredParticleSystem::RandomVector(1), ((float)rand() * 0.01) / RAND_MAX);
	tetra->ConvexPolyhedron::SetDebugColour(Vec4(ColouredParticleSystem::RandomVector(1), 1));
	PhysicsSystem::GetCurrentInstance()->AddRigidBody(tetra);
}

void setup()
{
	srand(time(NULL));
	camera = new FPSCamera();
	cameraController = new CameraController();
	cameraController->SetCamera(camera);
	camera->Position = Vec3(0.0, 0.0, -5.0f);
	cameraController->HasMomentum = true;
	glutWarpPointer(width / 2, height/ 2);
	cameraController->HasAngularMomentum = true;
	cameraController->MaxSpeed = 0.25f;
	for (int i = 0; i < 255; ++i)
	{
		keystate[i] = false;
		lastKeystate[i] = false;
	}
	glutSetCursor(GLUT_CURSOR_NONE);
	groundPlane = new Plane(Vec3(0.0, 1.0, 0.0), Vec3(0.0, 0.0, 0.0));
	PhysicsSystem::GetCurrentInstance()->AddCollidable(groundPlane);

	for (int i = 0; i < numBoxes; ++i)
	{
		AddBox();
	}

	testBox = boxes[0];
	testVel = testBox->GetVelocity();
	testBox->RigidBody::SetDebugColour(Vec4(1, 0, 0, 1));

	PhysicsSystem::GetCurrentInstance()->SetDebugDrawer(new DefaultDebugDrawer());
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	float spec[4];
	spec[0] = 1.0f;
	spec[1] = 1.0f;
	spec[2] = 1.0f;
	spec[3] = 1.0f;
	Vec4 amb(0.01f, 0.01f, 0.01f, 0.01f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb.Ref());
	glEnable(GL_LIGHT0);
	Vec4 diffColour(1.0f, 0.3f, 0.3f, 1.0f);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffColour.Ref());

}

int lastTime = 0;
int frameCounter = 0;
int frameTimeCount = 0;

void display ()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int elapsedTime = (currentTime - lastTime);
	lastTime = currentTime;

	glEnable(GL_DEPTH_TEST);

	++frameCounter;
	frameTimeCount += elapsedTime;

	if (frameTimeCount > 1000)
	{
		frameTimeCount = 0;
		fps = frameCounter;
		frameCounter = 0;
	}

	cameraController->Update((float)elapsedTime);
	if (physicsActive)
		PhysicsSystem::GetCurrentInstance()->Integrate((float)elapsedTime / 1000.0f);
	Vec4 lightPos(0.0f, 100.0f, 10.0f, 1.0f);

 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMultMatrixf(camera->GetViewTransform().Ref()); //apply camera transform
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos.Ref());
	
	
	groundPlane->Draw();

	for (int i = 0; i < boxes.size(); ++i)
	{
		//boxes[i]->Draw();
		Vec3& pos = boxes[i]->GetPosition();
		Vec3& vel = boxes[i]->GetVelocity();
		Vec3 imp = Vec3(0, 0, 0);
		
		for (int j = 0; j < 3; ++j)
		{		
			if (pos[j] > maxPos[j])	
			{
				imp[j] = maxPos[j] - pos[j];						
			}
			else if (pos[j] < minPos[j])
			{
				imp[j] = minPos[j] - pos[j];
			}
			boxes[i]->ApplyForce(imp);	
		}		

	}

	glDisable(GL_LIGHTING);
	PhysicsSystem::GetCurrentInstance()->DrawDebug();
	PhysicsSystem::GetCurrentInstance()->GetDebugDrawer()->DrawAABB(bounds, Vec4(0, 0, 1, 1));
	/*
	//Draw model axes.
	glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 2, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 2);
	glEnd();
	*/

	glutSwapBuffers();
}

void HandleInput()
{
	if (keystate['w'])
	{
		cameraController->MoveForward();
	}
	else if (keystate['s'])
	{
		cameraController->MoveBackward();
	}

	if (keystate['a'])
	{
		cameraController->MoveLeft();
	}
	else if (keystate['d'])
	{
		cameraController->MoveRight();
	}

	if (keystate[' '])
	{
		cameraController->MoveUp();
	}
	else if (keystate['c'])
	{
		cameraController->MoveDown();
	}

	if (keystate['b'] && !lastKeystate['b'])
	{
		AddBox();
	}
	if (keystate['q'] && !lastKeystate['q'])
		AddTetra();
	if (keystate['p'] && !lastKeystate['p'])
		physicsActive = !physicsActive;
	
	if (keystate[27])
		exit(0);
	if (keystate['h'])
	{
		int i = 0;
		testBox = testBox;
	}
	if (keystate['t'] && !lastKeystate['t'])
		PhysicsSystem::GetCurrentInstance()->Integrate(0.016f);

	memcpy(lastKeystate, keystate, sizeof(bool) * 256);

}

// This function is called when there is nothing else to do.
void idle ()
{

	HandleInput();

	const double STEP = 0.1;
	const double ALL_ROUND = 360;
	alpha += STEP;
	if (alpha > ALL_ROUND)
		alpha -= ALL_ROUND;

	// Display normalized coordinates in title bar.
	const int BUFSIZE = 200;
	static char buffer[BUFSIZE];
	ostrstream s(buffer, BUFSIZE);
	s << 
		resetiosflags(ios::floatfield) << setiosflags(ios::fixed) << 
		setprecision(3) << "Camera pitch, yaw: " << camera->Pitch << ", " << camera->Yaw << 
		setprecision(0) << ").  Position=" << setw(3) << camera->Position[0] << ", " << camera->Position[1] << ", " << camera->Position[2] <<		
		setprecision(2) << ".  fps=" << fps <<
		"." << ends;
	glutSetWindowTitle(buffer);

	dMouseX = (xMouse - width / 2.0f);
	dMouseY = (yMouse - height / 2.0f);

	cameraController->ChangePitch(-dMouseY);
	cameraController->ChangeYaw(-dMouseX);
	glutWarpPointer(width / 2, height / 2);

	glutPostRedisplay();
}

void mouseMovement (int mx, int my)
{
   // Normalize mouse coordinates.
   xMouse = float(mx);
   yMouse = float(my);

   // Redisplay image.
   glutPostRedisplay();
}

// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
   width = newWidth;
   height = newHeight;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
   gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}

// Display help.
void help()
{
   cout << 
      "'h'   display help" << endl <<
      endl;
}

// Respond to graphic character keys.
// Parameters give key code and mouse coordinates.
void KeyDown (unsigned char key, int x, int y)
{
	keystate[key] = true;
}

void KeyUp (unsigned char key, int x, int y)
{
	keystate[key] = false;
}

// Respond to function keys.
// Parameters give key code and mouse coordinates.
void functionKeys (int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		cout << "F1" << endl;
		break;
	case GLUT_KEY_UP:
		cout << "Up" << endl;
		break;	  
	}
}


void main (int argc, char **argv)
{
	// GLUT initialization.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("GLUT Skeleton Program");
	setup();
	// Register call backs.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(KeyDown);
	glutKeyboardUpFunc(KeyUp);
	glutSpecialFunc(functionKeys);
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement);
	glutIdleFunc(idle);

	// OpenGL initialization
	glEnable(GL_DEPTH_TEST);

	// Display help.
	help();

	// Enter GLUT loop.
	glutMainLoop();
}
