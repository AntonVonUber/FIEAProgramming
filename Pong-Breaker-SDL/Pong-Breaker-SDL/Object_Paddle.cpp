#include "Object_Paddle.h"

Object_Paddle::Object_Paddle( Vector2D pos,
	std::string fileName)
:	m_fileName(fileName),
	m_texture(nullptr)
{
	m_pos = pos;
	m_vel = Vector2D();
	m_ID = "paddle";
	m_leftPressed = false;
	m_rightPressed = false;
}
Object_Paddle::~Object_Paddle()
{
	Cleanup();
}

void Object_Paddle::Init()
{
	m_texture = Window::LoadImage(m_fileName);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
	m_xOffset = (m_rect.w / 2);
	m_yOffset = m_rect.h;
	setPos(m_pos);
}

void Object_Paddle::Update(Application* game,
	float deltaTime)
{
	// if both left and right are pressed,
	// nothing happens... stand still!
	if(leftIsPressed() && rightIsPressed())
		setVel(0,0);
	// if left is pressed, a leftward
	// velocity is applied
	else if(leftIsPressed())
		setVel(-5,0);
	// if right is pressed, a rightward
	// velocity is applied
	else if(rightIsPressed())
		setVel(5,0);
	// otherwise, if neither left nor
	// right is pressed, DON'T MOVE!
	else
		setVel(0,0);
	setPos(getPos() + (getVel()*deltaTime));

	// keeps the paddle within the bounds of the level
	if((getPos().x + m_xOffset) > Window::Box().w)
		setPos((Window::Box().w - m_xOffset),getPos().y);
	else if((getPos().x - m_xOffset) < Window::Box().x)
		setPos((Window::Box().x + m_xOffset),getPos().y);
}

// draw the paddle to the screen
void Object_Paddle::Draw(Application* game)
{
	game->m_window.Draw(m_texture, m_rect);
}

// all dynamic memory objects are cleaned up
void Object_Paddle::Cleanup()
{
	if(m_texture != NULL)
		SDL_DestroyTexture(m_texture);
}