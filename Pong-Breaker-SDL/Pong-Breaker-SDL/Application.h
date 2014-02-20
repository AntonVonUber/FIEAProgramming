#ifndef	__APPLICATION_H__
#define __APPLICATION_H__

#include "SDL.h"
#include "Window.h"
#include "Defines.h"
#include "Vector2D.h"

#include <vector>
using namespace std;

class GameState;

class Application
{
public:
    Application() { }
	~Application() { Shutdown(); }

	void	Init(std::string title = WINDOW_TITLE, int x = 50, int y = 50,
				int width=WINDOW_WIDTH, int height=WINDOW_HEIGHT, bool fullscreen=false); // add other flags?
	void	Run();
	void	ChangeState(GameState* state);
	void	PushState(GameState* state);
	void	PopState();
	void	Shutdown();

	// Contents of main loop
	void	HandleEvents();
	void	Update();
	void	Draw();

	bool	isRunning() { return m_running; }
	void	Quit() { m_running = false; }

	Window	m_window;	// might make public...

private:
	Application(Application const&) { };	// Don't Implement.
	void operator=(Application const&) { };	// Don't implement.

//	static Application instance;

	// the stack of states
	vector<GameState*>		states;

	bool					m_running;
	bool					m_fullScreen;
};

#endif	//	__APPLICATION_H__