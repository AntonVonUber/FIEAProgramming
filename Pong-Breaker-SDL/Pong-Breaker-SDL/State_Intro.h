#ifndef __STATE_INTRO_H__
#define __STATE_INTRO_H__

#include <sstream>

#include "SDL.h"
#include "GameState.h"
//#include "Timer.h"	// if making a time-based fade-in...

class State_Intro : public GameState
{
public:
	void Init();
	void Pause();
	void Resume();
	void HandleEvents(Application* game);
	void Update(Application* game);
	void Draw(Application* game);
	void Cleanup();

	static State_Intro* getInstance() {
		return &m_introState;
	}

protected:
	State_Intro() { }
	~State_Intro() { Cleanup(); }

private:
	static State_Intro m_introState;

//	Timer				timer;

    // Textures to display a message and
	// show the splash screen
    SDL_Texture*		msgTexture;
	SDL_Texture*		splashScreen;	//, *fadeScreen;
	//Rects for the text
	SDL_Rect			msgBox, splashBox, fadeBox;
//	int					alpha;	// for when fading in is applied
    // Color for the text
    SDL_Color			black;
};

#endif	// __STATE_INTRO_H__