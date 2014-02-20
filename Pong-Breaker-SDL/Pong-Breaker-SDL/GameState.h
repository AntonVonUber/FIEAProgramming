#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include "Application.h"
#include "Vector2D.h"

// all game states, play, menu, intro,
// etc., inherit from this superclass
class GameState
{
public:
	virtual void Init() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void HandleEvents(Application* game) = 0;
	virtual void Update(Application* game) = 0;
	virtual void Draw(Application* game) = 0;
	virtual void Cleanup() = 0;

	void ChangeState(Application* game, GameState* state) {
		game->ChangeState(state);
	}

protected:
	GameState() { }
};

#endif	// __GAME_STATE_H__