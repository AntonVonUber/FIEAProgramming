#include "Application.h"
#include "Scene.h"

#include "Windows.h"

#include <iostream>

using namespace std;


Application* Application::s_instance = NULL;

// right now doesn't test/ensure that Application is a
// singleton ... but Application IS a singleton - there
// should only be one instance of Application at a time
Application::Application()
:	s_title("Gravity Demo"),
	s_width(800),
	s_height(600)
{
	s_instance = this;
}


Application::~Application()
{
	if(s_instance)
		s_instance->destroyInstance();
}


void Application::destroyInstance()
{
	// ADD CODE TO DESTROY/FREE PARTS OF INSTANCE
	s_scene.close();

	// ends with this line:
	s_instance = NULL;
}


int Application::initialize(int argc, char **argv)
{
	initGraphics(argc, argv);
	//s_currentTime = clock();
	s_prevTime = clock();

	return 0;
}

int Application::run()
{
	// initialize the scene
	s_scene.initialize();

	glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );
	glutMainLoop();

	return 0;
}


void Application::quit()
{
	glutLeaveMainLoop();
}


void Application::initGraphics(int argc, char **argv)
{
	// starts graphics with glut
	glutInit(&argc, argv);

	// initializes window size
	glutInitWindowSize (s_width, s_height);
	// -1 as parameters means the window manager
	// will decide where the window will appear
    glutInitWindowPosition (0, 0);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// param is the const char* title of the window
    glutSetWindow(glutCreateWindow (s_title));

	if(glGetError() != GL_NO_ERROR)
	{
		cout << "Failed to create glut Window." << endl;
		exit(0);
	}

	// register callbacks
//	glutCloseFunc(exitCallbackWrapper);

	glutDisplayFunc(renderCallbackWrapper);
	glutReshapeFunc(reshapeCallbackWrapper);
	glutIdleFunc(idleCallbackWrapper);

/*	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboardCallbackWrapper);
	glutKeyboardUpFunc(keyboardUpCallbackWrapper);
	glutSpecialFunc(specialCallbackWrapper);
	glutSpecialUpFunc(specialUpCallbackWrapper);

	// Functions added to the sample framework
	glutMouseFunc(mouseCallbackWrapper);
	glutPassiveMotionFunc(mouseMoveCallbackWrapper);
*/


	if(glGetError() != GL_NO_ERROR)
	{
		cout << "Failed to register glut callbacks." << endl;
		exit(0);
	}


	// setup default render states
	glClearColor(0.f, 0.f, 0.f, 1.0f);	// sets the clear color to black
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//glEnable(GL_LIGHT_MODEL_TWO_SIDE);
	//glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
}


void Application::renderCallbackWrapper()
{
	if(s_instance)
		s_instance->renderCallback();
}
void Application::renderCallback()
{
	update();
	s_scene.render();
}


void Application::reshapeCallbackWrapper(int width, int height)
{
	if(s_instance)
		s_instance->reshapeCallback(width, height);
}
void Application::reshapeCallback(int width, int height)
{
	if(height == 0 )
		height = 1;

	s_width = width;
	s_height = height;

	float ratio = (float)s_width / s_height;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, s_width, s_height);

	// Set the correct perspective
//	gluPerspective(45, ratio, -3e4, 6e6);
	gluPerspective(45, ratio, 10, -10);
//	gluPerspective(45, ratio, 1, 100);

	// Get back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void Application::idleCallbackWrapper()
{
	if(s_instance)
		s_instance->idleCallback();
}
void Application::idleCallback()
{
	renderCallback();
}


void Application::update()
{
	s_currentTime = clock();
	s_scene.update((float)((s_currentTime - s_prevTime)));	//	/CLOCKS_PER_SEC));
//	std::cout << "cur - prev: " << ((float)(s_currentTime - s_prevTime)/CLOCKS_PER_SEC) << endl;
	s_prevTime = s_currentTime;
}