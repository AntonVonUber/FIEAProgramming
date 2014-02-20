// Necessary to go to Project->Properties->
// C/C++ folder->Code Generation->
// Runtime Library->Multi-threaded DLL (/MD)
//
// Properties-->Linker-->Linker-->Input-->
//	Additional Dependencies-->sdl.lib;sdlmain.lib;
//
// *** NECESSARY FOR SDL ***

//#pragma comment(lib, "SDL2.lib")
//#pragma comment(lib, "SDL2main.lib")
//#pragma comment(lib, "SDL2_TFF.lib")

#include <cstdio>
#include <vector>

#include "SDL.h"
#include "Application.h"
#include "GameState.h"
#include "State_Intro.h"

void Application::Init(std::string title, int x, int y,
	int width, int height, bool fullscreen)	// add more flags, as desired
{
	int flags = 0;

	if ( fullscreen ) {
		flags = SDL_WINDOW_FULLSCREEN;
	}
	else {
		flags = SDL_WINDOW_SHOWN;
	}

	m_window.Init(title, x, y, width, height, flags);

	m_fullScreen = fullscreen;
	m_running = true;

	printf("Application Init\n");
}

void Application::Run()
{
	ChangeState( State_Intro::getInstance() );

	// main loop
	while ( isRunning() )
	{
		HandleEvents();
		Update();
		Draw();
	}
}

void Application::Shutdown()	// was previously Cleanup();
{
	// cleanup the all states
	while ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// switch back to windowed mode so other 
	// programs won't get accidentally resized
	if ( m_fullScreen ) {
		// might not work... work on this later...
		m_window.Resize();
	}

	printf("Application Cleanup\n");

	m_window.Quit();
}


void Application::ChangeState(GameState* state) 
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void Application::PushState(GameState* state)
{
	// pause current state
	if ( !states.empty() ) {
		states.back()->Pause();
	}

	// store and init the new state
	states.push_back(state);
	states.back()->Init();
}

void Application::PopState()
{
	// cleanup the current state
	if ( !states.empty() ) {
		states.back()->Cleanup();
		states.pop_back();
	}

	// resume previous state
	if ( !states.empty() ) {
		states.back()->Resume();
	}
}


void Application::HandleEvents() 
{
	// let the state handle events
	states.back()->HandleEvents(this);
}

void Application::Update() 
{
	// let the state update the game
	states.back()->Update(this);
}

void Application::Draw() 
{
	// let the state draw the screen
	states.back()->Draw(this);
}

/*#include <string>
#include <stack>			// We'll use the STL stack to store our function pointers
#include <iostream>
#include "SDL_TTF.h"		// True Type Font header
#include "Defines.h"		// Our defines header
#include "Application.h"	// Our Application


// This function initializes our game. //
void Application::Init()//WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN)
{
	// Initiliaze SDL video and our timer. //
	if(SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER) == -1){
		std::cout << SDL_GetError() << std::endl;
		return;	// change to return type int for different 'fails'
	}

	g_Window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	/*
		WINDOW_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		0, 0,
		SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL );
		//SDL_WINDOW_FULLSCREEN_DESKTOP);

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

	if( g_Window == NULL ) {
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	g_Renderer = SDL_CreateRenderer( g_Window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );//0);
	if( g_Renderer == NULL ) {
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	// Initialize the true type font library. //
	if(TTF_Init() == -1){
		std::cout << TTF_GetError() << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_Renderer);
	SDL_RenderPresent(g_Renderer);

	// Get the number of ticks since SDL was initialized. //
	g_Timer = SDL_GetTicks();

	// Fill our texture with information. //
	g_Texture = LoadImage("data/background2.bmp");
//	pushTexture(g_Texture);

/*	// We start by adding a pointer to our exit state, this way //
	// it will be the last thing the player sees of the game.   //
	StateStruct state;
	state.StatePointer = Exit;
	g_StateStack.push(state);

	// Then we add a pointer to our menu state, this will //
	// be the first thing the player sees of our game.    //
	state.StatePointer = Menu;
	g_StateStack.push(state);
}


void Application::Run()
{
/*	// Our game loop is just a while loop that breaks when our state stack is empty. //
	while (!g_StateStack.empty())
	{
		g_StateStack.top().StatePointer();		
	}
//	SDL_Color RedTest = {255,0,0};
//	SDL_Texture* temp = RenderText("Hello", "ARIAL.TTF", RedTest, 700);	// YAY!  It worked!
	SDL_RenderClear(g_Renderer);
//    SDL_RenderCopy(g_Renderer, temp, NULL, NULL);
	SDL_RenderCopy(g_Renderer, g_Texture, NULL, NULL);
    SDL_RenderPresent(g_Renderer);
	SDL_Delay(5000);
//	SDL_DestroyTexture(temp);
}


SDL_Texture* Application::LoadImage(const std::string &imgFile){
    SDL_Surface *loadedImage = nullptr;
    SDL_Texture *texture = nullptr;

	// SDL_LoadIMG("something.png");	// but it's a separate library...
    loadedImage = SDL_LoadBMP(imgFile.c_str());
    if (loadedImage != nullptr){
        texture = SDL_CreateTextureFromSurface(g_Renderer, loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
        std::cout << SDL_GetError() << std::endl;
    return texture;
}

void Application::ApplySurface(int x, int y, SDL_Texture *tex){	//, SDL_Renderer *rend){
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
 
	// NULL is for taking a PORTION of the texture...
    SDL_RenderCopy(g_Renderer, tex, NULL, &pos);
}


// This function shuts down our game. //
void Application::Shutdown()
{
	// Shutdown the true type font library. //
	//TTF_Quit();

	/*for(TexturesIterator iter = getFirstTexture();
		iter != getLastTexture();
		)//++iter)
	{
		SDL_DestroyTexture((*iter));
		delete *iter;
	}
	s_textures.erase(s_textures.begin(), s_textures.end());	
	SDL_DestroyTexture(g_Texture);
	SDL_DestroyRenderer(g_Renderer);
	SDL_DestroyWindow(g_Window);

	// Tell SDL to shutdown and free any resources it was using. //
	SDL_Quit();
}


void Application::DrawBackground() {}
// This function simply clears the back buffer to black. //
void Application::ClearScreen()
{
	// Clears the screen to black. //
	SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
	SDL_RenderClear(g_Renderer);
}
void Application::SwapBuffers() {}

// This function handles the game's main menu. From here //
// the player can select to enter the game, or quit.     //
/*void Application::Menu()
{
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleMenuInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		DisplayText("Start (G)ame", 350, 250, 12, 255, 255, 255, 0, 0, 0);
		DisplayText("(Q)uit Game",  350, 270, 12, 255, 255, 255, 0, 0, 0);
			
		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		//SDL_UpdateRect(g_Window, 0, 0, 0, 0);
		//SDL_Flip(g_Window);
		SDL_RenderPresent(g_Renderer);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function handles the main game. We'll control the   //
// drawing of the game as well as any necessary game logic. //
void Application::Game()
{	
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleGameInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		// Draw the background of our little 'game'. //
		DrawBackground();

		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		//SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function handles the game's exit screen. It will display //
// a message asking if the player really wants to quit.          //
void Application::Exit()
{	
	// Here we compare the difference between the current time and the last time we //
	// handled a frame. If FRAME_RATE amount of time has, it's time for a new frame. //
	if ( (SDL_GetTicks() - g_Timer) >= FRAME_RATE )
	{
		HandleExitInput();

		// Make sure nothing from the last frame is still drawn. //
		ClearScreen();

		DisplayText("Quit Game (Y or N)?", 350, 250, 12, 255, 255, 255, 0, 0, 0);

		// Tell SDL to display our backbuffer. The four 0's will make //
		// SDL display the whole screen. //
		//SDL_UpdateRect(g_Window, 0, 0, 0, 0);

		// We've processed a frame so we now need to record the time at which we did it. //
		// This way we can compare this time the next time our function gets called and  //
		// see if enough time has passed between iterations. //
		g_Timer = SDL_GetTicks();
	}	
}

// This function draws the background //
void Application::DrawBackground() 
{
	// These structures tell SDL_BlitSurface() the location of what //
	// we want to blit and the destination we want it blitted to.   //
	// Presently, we blit the entire surface to the entire screen.  //
	SDL_Rect source      = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };		
	SDL_Rect destination = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	
	// This just 'block-image transfers' our bitmap to our window. //
	//SDL_BlitSurface(g_Bitmap, &source, g_Window, &destination);
}



SDL_Texture* Application::RenderText(std::string message,
	std::string fontFile, SDL_Color color, int fontSize)
{
	//Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
        throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
	
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(g_Renderer, surf);
    //Clean up unneeded stuff
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
 
    return texture;
}


// This function displays text to the screen. It takes the text //
// to be displayed, the location to display it, the size of the //
// text, and the color of the text and background.              //
void Application::DisplayText(std::string text, int x, int y, int size, int fR, int fG, int fB, int bR, int bG, int bB) 
{
	// Open our font and set its size to the given parameter. //
    TTF_Font* font = TTF_OpenFont("arial.ttf", size);

	SDL_Color foreground  = { fR, fG, fB};   // Text color. //
	SDL_Color background  = { bR, bG, bB };  // Color of what's behind the text. //

	// This renders our text to a temporary surface. There //
	// are other text functions, but this one looks nice.  //
	SDL_Surface* temp = TTF_RenderText_Shaded(font, text.c_str(), foreground, background);

	// A structure storing the destination of our text. //
	SDL_Rect destination = { x, y, 0, 0 };
	
	// Blit the text surface to our window surface. //
	//SDL_BlitSurface(temp, NULL, g_Window, &destination);	//************

	// Always free memory! //
	SDL_FreeSurface(temp);

	// Close the font. //
	TTF_CloseFont(font);
}	*/
/*
// This function receives player input and //
// handles it for the game's menu screen.  //
void Application::HandleMenuInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				return;  // this state is done, exit the function 
			}
			// Quit //
			if (g_Event.key.keysym.sym == SDLK_q)
			{
				g_StateStack.pop();
				return;  // game is over, exit the function 
			}
			// Start Game //
			if (g_Event.key.keysym.sym == SDLK_g)
			{
				StateStruct temp;
				temp.StatePointer = Game;
				g_StateStack.push(temp);
				return;  // this state is done, exit the function 
			}
		}
	}
}

// This function receives player input and //
// handles it for the main game state.     //
void Application::HandleGameInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				
				return;  // this state is done, exit the function 
			}			
		}
	}
}

// This function receives player input and //
// handles it for the game's exit screen.  //
void Application::HandleExitInput() 
{
	// Fill our event structure with event information. //
	if ( SDL_PollEvent(&g_Event) )
	{
		// Handle user manually closing game window //
		if (g_Event.type == SDL_QUIT)
		{			
			// While state stack isn't empty, pop //
			while (!g_StateStack.empty())
			{
				g_StateStack.pop();
			}

			return;  // game is over, exit the function
		}

		// Handle keyboard input here //
		if (g_Event.type == SDL_KEYDOWN)
		{
			if (g_Event.key.keysym.sym == SDLK_ESCAPE)
			{
				g_StateStack.pop();
				
				return;  // this state is done, exit the function 
			}
			// Yes //
			if (g_Event.key.keysym.sym == SDLK_y)
			{
				g_StateStack.pop();
				return;  // game is over, exit the function 
			}
			// No //
			if (g_Event.key.keysym.sym == SDLK_n)
			{
				StateStruct temp;
				temp.StatePointer = Menu;
				g_StateStack.push(temp);
				return;  // this state is done, exit the function 
			}
		}
	}
}	*/