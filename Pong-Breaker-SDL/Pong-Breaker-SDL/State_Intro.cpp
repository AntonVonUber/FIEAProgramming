#include <cstdio>

#include "SDL.h"
#include "Application.h"

#include "GameState.h"
#include "State_Intro.h"
#include "State_Play.h"

State_Intro State_Intro::m_introState;

void State_Intro::Init()
{
	msgTexture = nullptr;
	splashScreen = nullptr;
	black = SDL_BLACK;

	splashScreen = Window::LoadImage("images\\splashScreen.png");
	SDL_QueryTexture(splashScreen, NULL, NULL, &splashBox.w, &splashBox.h);
	splashBox.x = 0;
	splashBox.y = 0;

	//Setup msg text
    msgTexture = Window::RenderText("<< "+SPACEBAR_STRING+" >>", "Arial.ttf", black, 30);
	SDL_QueryTexture(msgTexture, NULL, NULL, &msgBox.w, &msgBox.h);
	msgBox.x = Window::Box().w/2 - (msgBox.w/2);
    msgBox.y = Window::Box().h * 0.85;

	printf("State_Intro Init\n");
}

void State_Intro::Pause()
{
	printf("State_Intro Pause\n");
}
void State_Intro::Resume()
{
	printf("State_Intro Resume\n");
}

void State_Intro::HandleEvents(Application* game)
{
	SDL_Event event;	// should probably be part of header file...

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_SPACE:
						game->ChangeState( State_Play::getInstance() );
						break;

					//For quitting, escape key
					case SDLK_x:
					case SDLK_q:
					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;
		}
	}
}

void State_Intro::Update(Application* game) 
{
	// To have a fade-in effect later, perhaps
/*	--alpha;
	alpha-=20;

	if (alpha < 0)
		alpha = 0;	*/
}

void State_Intro::Draw(Application* game) 
{
	game->m_window.Clear();
//	game->m_window.DrawRectangle(255, 0, 0, 255, fadeBox);
	game->m_window.Draw(splashScreen, splashBox);
	game->m_window.Draw(msgTexture, msgBox);
	game->m_window.Present();
}

void State_Intro::Cleanup()
{
	if(msgTexture != NULL)
		SDL_DestroyTexture(msgTexture);
	if(splashScreen != NULL)
		SDL_DestroyTexture(splashScreen);
//	if(fadeScreen != NULL)
//		SDL_DestroyTexture(fadeScreen);

	printf("State_Intro Cleanup\n");
}