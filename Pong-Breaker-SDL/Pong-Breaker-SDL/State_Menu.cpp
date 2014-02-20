#include <cstdio>

#include "SDL.h"
#include "Application.h"

#include "GameState.h"
#include "State_Menu.h"
#include "State_Play.h"

State_Menu State_Menu::m_menuState;

void State_Menu::Init()
{
	msg = nullptr;
	msg2 = nullptr;
	black = SDL_BLACK;

	// setup msg and msg2 text
    msg = Window::RenderText("THIS IS CURRENTLY FOR SHOW", "Arial.ttf", black, 30);
    // query width and height from texture
    SDL_QueryTexture(msg, NULL, NULL, &msgBox.w, &msgBox.h);
    msgBox.x = (Window::Box().w/2) - (msgBox.w/2);
    msgBox.y = Window::Box().h * 0.6;

	msg2 = Window::RenderText("PRESS 'ESC' TO RETURN", "Arial.ttf", black, 30);
    // query width and height from texture
    SDL_QueryTexture(msg2, NULL, NULL, &msgBox2.w, &msgBox2.h);
    msgBox2.x = (Window::Box().w/2) - (msgBox2.w/2);
    msgBox2.y = Window::Box().h * 0.7;

	background = Window::LoadImage("images\\menuBackground.png");
    // query width and height from texture
    SDL_QueryTexture(background, NULL, NULL, &backgroundBox.w, &backgroundBox.h);
    backgroundBox.x = 0;
    backgroundBox.y = 0;
    
	printf("State_Menu Init\n");
}

void State_Menu::Cleanup()
{
	if(msg != NULL)
		SDL_DestroyTexture(msg);
    if(msg2 != NULL)
		SDL_DestroyTexture(msg2);
	if(background != NULL)
		SDL_DestroyTexture(background);

	printf("State_Menu Cleanup\n");
}

void State_Menu::Pause()
{
	printf("State_Menu Pause\n");
}

void State_Menu::Resume()
{
	printf("State_Menu Resume\n");
}

void State_Menu::HandleEvents(Application* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {

					//For quitting, escape key
					case SDLK_x:
					case SDLK_q:
					case SDLK_ESCAPE:
						game->PopState();
						break;
				}
				break;
		}
	}
}

void State_Menu::Update(Application* game) 
{
	// currently nothing here
	// - The Menu Class was just for show
	// to show the pushing and popping of
	// screens (gamestates)
}

void State_Menu::Draw(Application* game) 
{
	game->m_window.Clear();
	game->m_window.Draw(background, backgroundBox);
	game->m_window.Draw(msg, msgBox);
	game->m_window.Draw(msg2, msgBox2);
	game->m_window.Present();
}