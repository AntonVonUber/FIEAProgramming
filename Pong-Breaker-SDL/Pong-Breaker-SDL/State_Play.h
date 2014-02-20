#ifndef __STATE_PLAY_H__
#define __STATE_PLAY_H__

#include <sstream>
#include <set>

#include "SDL.h"
#include "GameState.h"
#include "Timer.h"
#include "GameObject.h"
#include "Object_Ball.h"
#include "Object_Paddle.h"
#include "Object_Brick.h"

class State_Play : public GameState
{
private:
	typedef std::set<GameObject*> ObjectList;

public:
	typedef ObjectList::size_type		ObjectsSizeType;
	typedef ObjectList::iterator		ObjectsIterator;
	typedef ObjectList::const_iterator	ConstObjectsIterator;

	void Init();
	void Pause();
	void Resume();
	void HandleEvents(Application* game);
	void Update(Application* game);
	void Draw(Application* game);
	void Cleanup();

	ObjectsIterator			getFirstObject() { return m_objects.begin(); } ;
	ConstObjectsIterator	getFirstObject() const { return m_objects.begin(); };

	ObjectsIterator			getLastObject() { return m_objects.end(); };
	ConstObjectsIterator	getLastObject() const { return m_objects.end(); };
	
	void					insertObject(GameObject* object) { m_objects.insert(object); };
	void					removeObject(GameObject* object) { m_objects.erase(object); };

	static State_Play* getInstance() {
		return &m_playState;
	}

protected:
	State_Play() { currentLevel = 1; numOfLevels = 4; score = 0; }
	~State_Play() { Cleanup(); }

private:
	static State_Play		m_playState;

	Timer					timer;
	int						prevTicks;

	int						score;
	int						lives;
//	bool					gameWon;	// currently unused
//	bool					gameLost;	// currently unused

	int						currentLevel;
	int						numOfLevels;

	//Color for the text
    SDL_Color				textColor;
    //Rects for the text
    SDL_Rect				msgBox, scoreBox, msgBox2, livesBox, backgroundBox;
    //Textures to display a message and earned score
	SDL_Texture*			msgTexture, *scoreTexture, *msgTexture2, *livesTexture, *backgroundTexture;
	std::stringstream		ssScore;	// TEST TO SEE IF YOU CAN USE THE SAME STRINGSTREAM...

	ObjectList				m_objects;
	Object_Ball*			m_ball;
	Object_Paddle*			m_paddle;
};

#endif	// __STATE_PLAY_H__