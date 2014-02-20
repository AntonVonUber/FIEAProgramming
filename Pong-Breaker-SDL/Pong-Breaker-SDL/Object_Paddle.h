#ifndef __OBJECT_PADDLE_H__
#define __OBJECT_PADDLE_H__

#include "GameObject.h"

class Object_Paddle : public GameObject
{
public:
	Object_Paddle( Vector2D vec2D=Vector2D(),
			std::string fileName="images\\paddle.png");
	~Object_Paddle();

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

	// functions particularto Object_Paddle's
	void			setLeftPressed(bool b) { m_leftPressed = b; };
	bool			leftIsPressed() { return m_leftPressed; };
	void			setRightPressed(bool b) { m_rightPressed = b; };
	bool			rightIsPressed() { return m_rightPressed; };

private:
	std::string		m_fileName;
	SDL_Texture*	m_texture;
	bool			m_leftPressed;
	bool			m_rightPressed;

	int				m_xOffset;
	int				m_yOffset;
};

#endif	//	__OBJECT_PADDLE_H__