#ifndef	__DEFINES_H__
#define __DEFINES_H__

//	Window Flags for SDL_CreateWindow
	//
	//	SDL_WINDOW_FULLSCREEN			-	fullscreen window
	//	SDL_WINDOW_FULLSCREEN_DESKTOP	-	fullscreen window at the
	//										current desktop resolution
	//	SDL_WINDOW_OPENGL				-	window usable with OpenGL context
	//	SDL_WINDOW_SHOWN				-	window is visible
	//	SDL_WINDOW_HIDDEN				-	window is not visible
	//	SDL_WINDOW_BORDERLESS			-	no window decoration
	//	SDL_WINDOW_RESIZABLE			-	window can be resized
	//	SDL_WINDOW_MINIMIZED			-	window is minimized
	//	SDL_WINDOW_MAXIMIZED			-	window is maximized
	//	SDL_WINDOW_INPUT_GRABBED		-	window has grabbed input focus
	//	SDL_WINDOW_INPUT_FOCUS			-	window has input focus
	//	SDL_WINDOW_MOUSE_FOCUS			-	window has mouse focus
	//	SDL_WINDOW_FOREIGN				-	window not created by SDL
	//	SDL_WINDOW_ALLOW_HIGHDPI		-	window should be created in high-DPI
	//										mode if supported (>= SDL 2.0.1)

//#define WINDOW_WIDTH		640  //800
//#define WINDOW_HEIGHT		480  //600
//#define WINDOW_TITLE		"SDL Pong Breaker"
//#define FRAMES_PER_SECOND	30
//#define FRAME_RATE			1000/FRAMES_PER_SECOND

static const int WINDOW_WIDTH			= 640;
static const int WINDOW_HEIGHT			= 480;
static const std::string WINDOW_TITLE	= "SDL Pong Breaker";

static const int FRAMES_PER_SECOND	= 30;
static const int FRAME_RATE			= 1000/FRAMES_PER_SECOND;

static const std::string PAUSE_STRING	= "PAUSED";
static const std::string SPACEBAR_STRING= "PRESS SPACE BAR TO START";
static const std::string MENU_STRING	= "PRESS 'M' FOR MENU";
static const std::string SCORE_STRING	= "Score: ";
static const std::string LIVES_STRING	= "Lives: ";

static const SDL_Color SDL_WHITE = {255,255,255};
static const SDL_Color SDL_BLACK = {0,0,0};
static const SDL_Color SDL_RED = {255,0,0}; 
static const SDL_Color SDL_GREEN = {0,255,0};
static const SDL_Color SDL_BLUE = {0,0,255};

#endif	// __DEFINES_H_