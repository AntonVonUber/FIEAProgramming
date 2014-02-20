#include "Object_Brick.h"

Object_Brick::Object_Brick( Vector2D vec2D,
	std::string fileName, int hp)
:	m_fileName(fileName),
	m_texture(nullptr)
{
	m_pos = vec2D;
	m_vel = Vector2D();
	m_ID = "brick";
	m_HP = hp;
}
Object_Brick::~Object_Brick()
{
	Cleanup();
}

void Object_Brick::Init()
{
	m_texture = Window::LoadImage(m_fileName);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
	m_xOffset = (m_rect.w / 2);
	m_yOffset = m_rect.h;
	setPos(m_pos);
}

// Nothing directly in 'Update' currently
void Object_Brick::Update(Application* game,
	float deltaTime)
{
	// No constantly updated activity needs to happen
	// to the bricks... collision handling is taken
	// care of by Update() function of 'State_Play'
}

// the HP of the brick decrements by one,
// and then the color of the brick changes
void Object_Brick::handleCollision()
{
	--m_HP;
	switch(m_HP)
	{
		case 4:
			m_fileName = "images\\brick_blue.png";
			break;
		case 3:
			m_fileName = "images\\brick_red.png";
			break;
		case 2:
			m_fileName = "images\\brick_orange.png";
			break;
		case 1:
			m_fileName = "images\\brick_yellow.png";
			break;
		default:
			m_fileName = "images\\brick_darkgrey.png";
	}
	Cleanup();
	m_texture = Window::LoadImage(m_fileName);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}

// the brick is drawn to the game window
void Object_Brick::Draw(Application* game)
{
	game->m_window.Draw(m_texture, m_rect);
}

// all dynamic memory objects are cleaned up
void Object_Brick::Cleanup()
{
	if(m_texture != NULL) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}