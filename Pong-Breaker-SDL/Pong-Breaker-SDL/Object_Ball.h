#ifndef __OBJECT_BALL_H__
#define __OBJECT_BALL_H__

#include "GameObject.h"
#include "Vector2D.h"

class Object_Ball : public GameObject
{
public:
	Object_Ball( Vector2D pos=Vector2D(0,0), Vector2D vel=Vector2D(0,0),
			std::string fileName="images\\ball.png");
	~Object_Ball();

	// accessor/mutators for position
	Vector2D		getPos() { return m_pos; };
	void			setPos(Vector2D p) { m_pos = p; m_rect.x=(int)(m_pos.x - m_xOffset); m_rect.y=(int)(m_pos.y - m_yOffset); };
	void			setPos(int x, int y) { m_pos.x = x; m_pos.y = y; m_rect.x = (x - m_xOffset); m_rect.y = (y - m_yOffset); };

	// accessor/mutators for velocity
	Vector2D		getVel() { return m_vel; };
	void			setVel(Vector2D v) { m_vel = v; };
	void			setVel(int x, int y) { m_vel.x = x; m_vel.y = y; };

	// standard functions shared by GameObjects
	virtual void	Init();
	virtual void	Update(Application* game,
						float deltaTime);
	virtual void	Draw(Application* game);
	virtual void	Cleanup();

	// functions particular to Object_Ball's
	bool			collisionTest(GameObject* go);
	bool			checkPointInRect(int x, int y, SDL_Rect rect);
	bool			isOutOfBounds() { return m_outOfBounds; };
	void			reset();
	float			getMinSpeed() { return m_minSpeed; };

private:
	std::string		m_fileName;
	SDL_Texture*	m_texture;

	int				m_radius;
	float			m_maxSpeedDiff;
	float			m_minSpeed;

	bool			m_outOfBounds;
	// starting position is remembered for when the ball
	// goes offscreen - then the game can 'restart' with
	// the ball starting from the same location for that
	// particular level
	Vector2D		m_startingPos;

	int				m_xOffset;
	int				m_yOffset;
};

#endif	//	__OBJECT_BALL_H__