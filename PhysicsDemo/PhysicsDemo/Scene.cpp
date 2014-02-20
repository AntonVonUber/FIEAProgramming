#include "Scene.h"
#include "Player.h"
#include "GravityOrb.h"
#include <time.h>

#include <cmath>
#include <iostream>

double angle = 0.0f;
void Scene::render()
{
	// Clears all pixels
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Currently rendered objects will be light-blue
	glColor3f (0.0, 0.5, 1.0);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	0.0f, 5.0f,  75.0f,
				0.0f, 5.0f,  0.0f,
				0.0f, 1.0f,  0.0f	);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	renderGrid();

	for(ObjectsIterator iter = getFirstObject(); iter != getLastObject(); ++iter)
	{
		(*iter)->render();
	}

	angle+=0.05f;
	//Sleep(1);

	glutSwapBuffers();
}


void Scene::renderGrid()
{
	int numXLines = 7;		// 1 + 6 units tall and deep
	int numYZLines = 11;	// 1 + 10 units wide (long)
	int halfXGrid = numXLines / 2;
	int halfYZGrid = numYZLines / 2;

	// Creates the GRID...
	glBegin(GL_LINES);
		for(int i = -halfYZGrid; i <= halfYZGrid; i++)
		{
			// +Y lines on XY plane
			glVertex3f((float)i, 0.0f, -3.0f);
			glVertex3f((float)i, (float)numXLines, -3.0f);

			// -Z lines on XZ plane
			glVertex3f((float)i, 0.0f, 4.0f);
			glVertex3f((float)i, 0.0f, (float)(-numXLines)+4.0f);
		}
		for(int i = 0; i <= numXLines; ++i)
		{
			// X lines on XZ plane
			glVertex3f((float)(-halfYZGrid), 0.0f, (float)(-i)+4.0f);
			glVertex3f((float)halfYZGrid, 0.0f, (float)(-i)+4.0f);

			// X lines on XY plane
			glVertex3f((float)(-halfYZGrid), (float)i, -3.0f);
			glVertex3f((float)halfYZGrid, (float)i, -3.0f);

			// +Y lines on YZ plane
			glVertex3f((float)halfYZGrid, 0.0f, (float)(-i)+4.0f);
			glVertex3f((float)halfYZGrid, (float)numXLines, (float)(-i)+4.0f);

			// -Z lines on YZ plane
			glVertex3f((float)halfYZGrid, (float)i, 4.0f);
			glVertex3f((float)halfYZGrid, (float)i, (float)(-numXLines)+4.0f);
		}
	glEnd();
}


void Scene::close()
{
	// delete all objects pushed on this scene
	for(ObjectsIterator iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		(*iter)->close();
		delete *iter;
	}
	m_objects.erase(m_objects.begin(), m_objects.end());
}


void Scene::update(float deltaTime)
{
	float deltat = (deltaTime/CLOCKS_PER_SEC) * 5;

	long double craftMass;

	Vector3 earthPos;
	Vector3 craftPos;

	long double rmagEarth;

	Vector3 pcraft;
	Vector3 fNet;

	long double earthRadius;

	// update the physics of each object in the scene-object-list
	for(ObjectsIterator iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if((*iter)->name() == "Earth")
		{
//			earthMass = (*iter)->mass();
			earthPos = (*iter)->position();
			earthRadius = ((*iter)->width())/2;
		}
		else
		{
			craftMass = (*iter)->mass();
			craftPos = (*iter)->position();
			pcraft = (*iter)->momentum();
		}
	}
	// calculate r-vector and |r|
	std::cout << "earthPos:(" << earthPos.x() << ", " << earthPos.y() << ", " << earthPos.z() << ")" << std::endl;
	Vector3 distance = earthPos.subtract(craftPos);
	rmagEarth = distance.mag();

	std::cout << "craftPos:(" << craftPos.x() << ", " << craftPos.y() << ", " << craftPos.z() << ")" << std::endl;
	std::cout << "distance:(" << distance.x() << ", " << distance.y() << ", " << distance.z() << ")" << std::endl;

/*	// calculate numerator of gravity formula
	float value = G*(earthMass*craftMass);
//	std::cout << "value: " << value << std::endl;
	Vector3 numerator = distance.scalarMult(value);

	std::cout << "numerator:(" << numerator.x() << ", " << numerator.y() << ", " << numerator.z() << ")" << std::endl;	*/

	// calculate F_net
//	fNet = numerator.scalarDiv(pow(rmagEarth,3));
	fNet = (distance.unitVector()).scalarMult(9.81f);

	// calculate new momentum
	fNet.scalarMult(deltat);
	pcraft = pcraft.add(fNet);

	// update position
	Vector3 temp = pcraft;
	temp.scalarMult(deltat/craftMass);
	craftPos = craftPos.add(temp);

	m_time += deltat;

	// update the physics of each object in the scene-object-list
	for(ObjectsIterator iter = m_objects.begin(); iter != m_objects.end(); ++iter)
	{
		if(((*iter)->name() != "Earth") && (rmagEarth >= earthRadius))
		{
			(*iter)->position(craftPos);
			(*iter)->momentum(pcraft);
		}
//		(*iter)->update();
	}
}


void Scene::initialize()
{
	SceneObject *gravOrb1 = new GravityOrb("Earth", Vector3(),
		Vector3(), 60.0f, 12.8f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	pushObject(gravOrb1);

	SceneObject *gravOrb2 = new GravityOrb("Moon", Vector3(10.0f, 0.0f, 0.0f),
		Vector3(), 40.0f, 6.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	pushObject(gravOrb2);

	SceneObject *player = new Player("Spaceship", Vector3(-10.0f, 0.0f, 0.0f),
		Vector3(0.0f, 1.0f, 0.0f), 15.0f, 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	pushObject(player);

	m_time = 0;
}