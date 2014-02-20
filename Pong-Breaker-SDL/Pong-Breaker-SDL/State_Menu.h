#ifndef __STATE_MENU_H__
#define __STATE_MENU_H__

#include <sstream>

#include "SDL.h"
#include "GameState.h"

class State_Menu : public GameState
{
public:
	void Init();
	void Pause();
	void Resume();
	void HandleEvents(Application* game);
	void Update(Application* game);
	void Draw(Application* game);
	void Cleanup();

	static State_Menu* getInstance() {
		return &m_menuState;
	}

protected:
	State_Menu() { }
	~State_Menu() { Cleanup(); }

private:
	static State_Menu m_menuState;

    //Textures to display a message
	SDL_Texture*		msg, *msg2, *background;
    //Color for the text
    SDL_Color			black;
    //Rects for the text
    SDL_Rect			msgBox, msgBox2, backgroundBox;
};

#endif	// __STATE_MENU_H__