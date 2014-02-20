#include <cstdio>
#include <ostream>
#include <fstream>

#include "SDL.h"
#include "Application.h"
#include "State_Play.h"
#include "State_Menu.h"
#include "LevelLoader.h"

State_Play State_Play::m_playState;

void State_Play::Init()
{
	msgTexture = nullptr;
	scoreTexture = nullptr;
	msgTexture2 = nullptr;
	livesTexture = nullptr;
	backgroundTexture = nullptr;

	// currently, upon beating a level OR losing,
	// the level changes, to show variety...
//	gameLost = false;
//	gameWon = false;

	lives = 3;

	textColor = SDL_RED;

	timer.Start();
	prevTicks = timer.Ticks();
	
	if(currentLevel > numOfLevels)
		currentLevel = 1;
	ssScore << "levels\\level" << currentLevel << ".txt";
	m_objects = LevelLoader::Load(ssScore.str());

	for(ObjectsIterator iter = getFirstObject(); iter != getLastObject(); ++iter)
	{
		if((*iter)->getID() == "ball")
			m_ball = dynamic_cast<Object_Ball*>(*iter);
		if((*iter)->getID() == "paddle")
			m_paddle = dynamic_cast<Object_Paddle*>(*iter);
	}
	// This portion is just to place the 'scoreBox' in
	// the appropriate location on screen, though initial
	// invisible because it's an empty string until the
	// player presses SPACEBAR
	msgTexture = Window::RenderText(SCORE_STRING, "Arial.ttf", textColor, 30);
	SDL_QueryTexture(msgTexture, NULL, NULL, &msgBox.w, &msgBox.h);
	SDL_DestroyTexture(msgTexture);
	scoreBox.x = msgBox.w + 20;
	scoreBox.y = (int)(Window::Box().h * 0.9);

	msgTexture2 = Window::RenderText(LIVES_STRING, "Arial.ttf", textColor, 30);
	SDL_QueryTexture(msgTexture2, NULL, NULL, &msgBox2.w, &msgBox2.h);
	SDL_DestroyTexture(msgTexture2);
	livesBox.x = Window::Box().w/2 + msgBox2.w + 20;
	livesBox.y = (int)(Window::Box().h * 0.9);

	backgroundTexture = Window::LoadImage("images\\darkBackground.png");
	SDL_QueryTexture(backgroundTexture, NULL, NULL, &backgroundBox.w, &backgroundBox.h);
	backgroundBox.x = 0;
	backgroundBox.y = 0;

	// Create the 'score text' texture
	msgTexture = Window::RenderText(SPACEBAR_STRING, "Arial.ttf", textColor, 30);
	SDL_QueryTexture(msgTexture, NULL, NULL, &msgBox.w, &msgBox.h);
	msgBox.x = Window::Box().w/2 - (msgBox.w/2);
    msgBox.y = (int)(Window::Box().h * 0.6);

	// Create the 'lives text' texture
	msgTexture2 = Window::RenderText(MENU_STRING, "Arial.ttf", textColor, 30);
	SDL_QueryTexture(msgTexture2, NULL, NULL, &msgBox2.w, &msgBox2.h);
	msgBox2.x = Window::Box().w/2 - (msgBox2.w/2);
    msgBox2.y = (int)(Window::Box().h * 0.7);


	printf("State_Play Init\n");
}

void State_Play::Pause()
{
	printf("State_Play Pause\n");
}

void State_Play::Resume()
{
	printf("State_Play Resume\n");
}

void State_Play::HandleEvents(Application* game)
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				game->Quit();
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_m:
						timer.Pause();
						game->PushState( State_Menu::getInstance() );
						break;

					case SDLK_SPACE:
						if((m_ball!=NULL)&&(m_ball->getVel() == Vector2D(0,0))) {
							m_ball->setVel(Vector2D(0.707,0.707)*m_ball->getMinSpeed());

							SDL_DestroyTexture(msgTexture);
							msgTexture = Window::RenderText(SCORE_STRING, "Arial.ttf", textColor, 30);
							SDL_QueryTexture(msgTexture, NULL, NULL, &msgBox.w, &msgBox.h);
							msgBox.x = 10;
							msgBox.y = (int)(Window::Box().h * 0.9);

						    scoreBox.x = msgBox.w + 20;
							scoreBox.y = (int)(Window::Box().h * 0.9);
							ssScore.str("");
							ssScore << score;
							SDL_DestroyTexture(scoreTexture);
							scoreTexture = Window::RenderText(ssScore.str(), "Arial.ttf", textColor, 30);
							ssScore.str("");

							SDL_DestroyTexture(msgTexture2);
							msgTexture2 = Window::RenderText(LIVES_STRING, "Arial.ttf", textColor, 30);
							SDL_QueryTexture(msgTexture2, NULL, NULL, &msgBox2.w, &msgBox2.h);
							msgBox2.x = Window::Box().w/2;
							msgBox2.y = (int)(Window::Box().h * 0.9);

							livesBox.x = Window::Box().w/2 + msgBox2.w + 20;
							livesBox.y = (int)(Window::Box().h * 0.9);
							ssScore.str("");
							ssScore << score;
							SDL_DestroyTexture(livesTexture);
							livesTexture = Window::RenderText(ssScore.str(), "Arial.ttf", textColor, 30);
							ssScore.str("");
						}
						if(!m_ball) {
							SDL_DestroyTexture(msgTexture);
							msgTexture = Window::RenderText("BALL NULL", "Arial.ttf", textColor, 30);
						}
						break;

					case SDLK_RIGHT:
						if(m_paddle!=NULL)
							m_paddle->setRightPressed(true);
						if(!m_paddle) {
							SDL_DestroyTexture(msgTexture);
							msgTexture = Window::RenderText("PADDLE NULL", "Arial.ttf", textColor, 30);
						}
						break;
					case SDLK_LEFT:
						if(m_paddle!=NULL)
							m_paddle->setLeftPressed(true);
						if(!m_paddle) {
							SDL_DestroyTexture(msgTexture);
							msgTexture = Window::RenderText("PADDLE NULL", "Arial.ttf", textColor, 30);
						}
						break;

					// no need to start and stop
					// the timer... so, add later?
					/*case SDLK_s:
						//If timer was running, stop it
						if (timer.Started())
							timer.Stop();
						else
							timer.Start();
						break;	*/

					case SDLK_p:
						if (timer.Paused())
							timer.Unpause();
						else
							timer.Pause();
						break;

					//For quitting, escape key
					case SDLK_x:
					case SDLK_q:
					case SDLK_ESCAPE:
						game->Quit();
						break;
				}
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_RIGHT:
						if(m_paddle!=NULL)
							m_paddle->setRightPressed(false);
						if(!m_paddle)
							msgTexture = Window::RenderText("NULL: ", "Arial.ttf", textColor, 30);
						break;
					case SDLK_LEFT:
						if(m_paddle!=NULL)
							m_paddle->setLeftPressed(false);
						if(!m_paddle)
							msgTexture = Window::RenderText("NULL: ", "Arial.ttf", textColor, 30);
						break;
				}
				break;
		}
	}
}

void State_Play::Update(Application* game) 
{
	// deltaTime changes the movement of
	// everything; and when it's zero,
	// movement of objects ceases
	float deltaTime = (float) (timer.Ticks() - prevTicks) / 20;	//1.0f;
	prevTicks = timer.Ticks();
	if(timer.Paused())
		deltaTime = 0.0f;

	if (timer.Started() && !timer.Paused())
	{
		ssScore.str("");
		if(!(m_ball->getVel() == Vector2D(0,0)))
			ssScore << score;
		SDL_DestroyTexture(scoreTexture);
		scoreTexture = game->m_window.RenderText(ssScore.str(), "Arial.ttf", textColor, 30);
		ssScore.str("");
		// Update the width and height of the text texture
		SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreBox.w, &scoreBox.h);

		// livesBox.x = msgBox2.w + 20;
		if(!(m_ball->getVel() == Vector2D(0,0)))
			ssScore << lives;
		SDL_DestroyTexture(livesTexture);
		livesTexture = game->m_window.RenderText(ssScore.str(), "Arial.ttf", textColor, 30);
		ssScore.str("");
		// Update the width and height of the text texture
		SDL_QueryTexture(livesTexture, NULL, NULL, &livesBox.w, &livesBox.h);
	}
	if (timer.Paused())
	{
		SDL_DestroyTexture(scoreTexture);
		scoreTexture = game->m_window.RenderText(PAUSE_STRING, "Arial.ttf", textColor, 30);
		ssScore.str("");
		// Update the width and height of the text texture
		SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreBox.w, &scoreBox.h);

		/*SDL_DestroyTexture(livesTexture);
		ssScore.str("");
		livesTexture = game->m_window.RenderText(ssScore.str(), "Arial.ttf", textColor, 30);
		ssScore.str("");
		// Update the width and height of the text texture
		SDL_QueryTexture(livesTexture, NULL, NULL, &livesBox.w, &livesBox.h);	*/
	}
	// a paddle will always be the last object, so it's 'OK' to
	// 'removeObject' after increasing the iterator because the
	// iterator will still point to one more object that needs
	// to be updated (the paddle) - only bricks can be removed
	int numOfBricks = 0;
	for(ObjectsIterator iter = getFirstObject(); iter != getLastObject(); ++iter)
	{
		if((*iter)->getID() != "ball")
		{
			if(m_ball->collisionTest(*iter) && ((*iter)->getID() == "brick"))
			{
				Object_Brick* temp = dynamic_cast<Object_Brick*>(*iter);
				temp->handleCollision();
				if(temp->getHP() <= 0) {
					++iter;
					// every destroyed block earns 10 points
					score+=10;		// if adding another player, this will call paddle member function...
					removeObject(temp);
				}
			}
			if((*iter)->getID() == "brick")
				++numOfBricks;
		}
		(*iter)->Update(game, deltaTime);
	}
	// if there's no more blocks, then that
	// means you've passed the level!
	if(numOfBricks == 0)
	{
		Cleanup();
		++currentLevel;
		Init();
	}
	if(m_ball->isOutOfBounds())
	{
		--lives;
		if(lives == 0) {
			Cleanup();
			++currentLevel;
			score = 0;
			Init();
		}
		else
		{
			m_ball->reset();
			SDL_DestroyTexture(msgTexture);
			msgTexture = Window::RenderText(SPACEBAR_STRING, "Arial.ttf", textColor, 30);
			SDL_QueryTexture(msgTexture, NULL, NULL, &msgBox.w, &msgBox.h);
			msgBox.x = Window::Box().w/2 - (msgBox.w/2);
			msgBox.y = (int)(Window::Box().h * 0.6);

			SDL_DestroyTexture(msgTexture2);
			msgTexture2 = Window::RenderText(MENU_STRING, "Arial.ttf", textColor, 30);
			SDL_QueryTexture(msgTexture2, NULL, NULL, &msgBox2.w, &msgBox2.h);
			msgBox2.x = Window::Box().w/2 - (msgBox2.w/2);
			msgBox2.y = (int)(Window::Box().h * 0.7);
		}
	}
}

void State_Play::Draw(Application* game) 
{
	game->m_window.Clear();
	game->m_window.Draw(backgroundTexture, backgroundBox);
	for(ObjectsIterator iter = getFirstObject(); iter != getLastObject(); ++iter)
	{
		(*iter)->Draw(game);
	}
	game->m_window.Draw(msgTexture, msgBox);
	game->m_window.Draw(scoreTexture, scoreBox);
	game->m_window.Draw(msgTexture2, msgBox2);
	game->m_window.Draw(livesTexture, livesBox);
	game->m_window.Present();
}

void State_Play::Cleanup()
{
	if(msgTexture != NULL)
		SDL_DestroyTexture(msgTexture);
	if(scoreTexture != NULL)
		SDL_DestroyTexture(scoreTexture);
	if(msgTexture2 != NULL)
		SDL_DestroyTexture(msgTexture2);
	if(livesTexture != NULL)
		SDL_DestroyTexture(livesTexture);
	if(backgroundTexture != NULL)
		SDL_DestroyTexture(backgroundTexture);

	for(ObjectsIterator iter = getFirstObject(); iter != getLastObject(); ++iter)
	{
		(*iter)->Cleanup();
	}
	m_ball = nullptr;
	m_paddle = nullptr;
	msgTexture = nullptr;
	scoreTexture = nullptr;
	msgTexture2 = nullptr;
	livesTexture = nullptr;

	printf("State_Play Cleanup\n");
}