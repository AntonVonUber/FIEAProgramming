#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "Application.h"

class GameObject
{
public:
	Vector2D	getPos() { return m_pos; };
	Vector2D	getVel() { return m_vel; };

	// pure virtual functions to be used
	// by the GameObject subclasses
	virtual void Init() = 0;
	virtual void Update(Application* game, float deltaTime) = 0;
	virtual void Draw(Application* game) = 0;
	virtual void Cleanup() = 0;

	std::string	getID() { return m_ID; };
	SDL_Rect	getRect() { return m_rect; };

protected:
	Vector2D	m_pos;
	Vector2D	m_vel;
	SDL_Rect	m_rect;

	// helps identify a particular GameObject
	std::string	m_ID;
};

#endif	//	__GAME_OBJECT_H__