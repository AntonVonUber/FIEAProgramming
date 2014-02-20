#ifndef __OBJECT_BRICK_H__
#define __OBJECT_BRICK_H__

#include "GameObject.h"

class Object_Brick : public GameObject
{
public:
	Object_Brick( Vector2D vec2D=Vector2D(),
			std::string fileName="images\\brick_red.png", int hp=3);
	~Object_Brick();

	// accessor/mutator for position
	Vector2D		getPos() { return m_pos; };
	void			setPos(Vector2D p) { m_pos = p; m_rect.x=(int)(m_pos.x - m_xOffset); m_rect.y=(int)(m_pos.y - m_yOffset); };

	// accessor/mutator for velocity
	Vector2D		getVel() { return m_vel; };
	void			setVel(Vector2D v) { m_vel = v; };

	// standard functions shared by GameObjects
	virtual void	Init();
	virtual void	Update(Application* game,
						float deltaTime);
	virtual void	Draw(Application* game);
	virtual void	Cleanup();

	// functions particular to Object_Brick's
	void			handleCollision();
	int				getHP() { return m_HP; };

private:
	std::string		m_fileName;
	SDL_Texture*	m_texture;
	int				m_HP;

	int				m_xOffset;
	int				m_yOffset;
};

#endif	//	__OBJECT_BRICK_H__