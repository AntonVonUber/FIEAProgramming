#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Scene.h"
#include <time.h>

class Application
{
public:
	Application();
	~Application();

	int				initialize(int argc, char **argv);
	int				run();
	void			quit();

protected:
	void			initGraphics(int argc, char **argv);

	// glut will only accept static functions as
	// callbacks, hence the static wrapper methods
	static	void	renderCallbackWrapper();
	void			renderCallback();

	static	void	reshapeCallbackWrapper(int width, int height);
	void			reshapeCallback(int width, int height);

	static	void	idleCallbackWrapper();
	void			idleCallback();

private:
	void			destroyInstance();
	void			update();

	// Private variables
	const char*		s_title;
	int				s_width;
	int				s_height;

	Scene			s_scene;

	clock_t			s_currentTime;
	clock_t			s_prevTime;

protected:
	static	Application*		s_instance;
};

#endif	// __APPLICATION_H__