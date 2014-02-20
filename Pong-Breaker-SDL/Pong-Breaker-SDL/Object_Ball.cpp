#include "Object_Ball.h"
//#include "Object_Paddle.h"

Object_Ball::Object_Ball( Vector2D pos,
	Vector2D vel, std::string fileName)
:	m_fileName(fileName),
	m_texture(nullptr)
{
	m_pos = pos;
	m_startingPos = pos;
	m_vel = vel;
	m_ID = "ball";
	m_maxSpeedDiff = 3;	// The max speed can be minSpeed + maxSpeedDiff
	m_minSpeed = 5;
	m_outOfBounds = false;
}
Object_Ball::~Object_Ball()
{
	Cleanup();
}

// initialize all appropriate values
void Object_Ball::Init()
{
	m_texture = Window::LoadImage(m_fileName);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
	m_xOffset = (m_rect.w / 2);
	m_yOffset = m_rect.h;
	setPos(m_startingPos);
	m_outOfBounds = false;

	m_radius = m_xOffset;
}

void Object_Ball::Update(Application* game,
	float deltaTime)
{
	// position update: newPos = curPos + Vel*deltaT
	setPos(getPos() + (getVel()*deltaTime));
	if((getRect().x + getRect().w) > Window::Box().w)
	{
		setVel(-(getVel().x),getVel().y);
		setPos(getPos().x - m_xOffset, getPos().y);
	}
	else if(getRect().x < Window::Box().x)
	{
		setVel(-(getVel().x),getVel().y);
		setPos(getPos().x + m_radius, getPos().y);
	}
	else if(getRect().y < Window::Box().y)//getPos().y < Window::Box().y)
	{
		setVel(getVel().x,-(getVel().y));
		setPos(getPos().x, getPos().y + m_radius);
	}
	else if(getRect().y + getRect().h > Window::Box().h)
	{
		m_outOfBounds = true;
	}
}
void Object_Ball::Draw(Application* game)
{
	game->m_window.Draw(m_texture, m_rect);
}
void Object_Ball::Cleanup()
{
	if(m_texture != NULL)
		SDL_DestroyTexture(m_texture);
}

bool Object_Ball::collisionTest(GameObject* go)
{
	bool returnVal = false;

	// Temporary values to save on typing
	// that represent the edges of the ball
	int left_x = m_rect.x;
	int left_y = m_rect.y + (m_rect.h/2);
	int right_x = m_rect.x + m_rect.w;
	int right_y = m_rect.y + (m_rect.h/2);
	int top_x = m_rect.x + (m_rect.w/2);
	int top_y = m_rect.y;
	int bottom_x = m_rect.x + (m_rect.w/2);
	int bottom_y = m_rect.y + m_rect.h;

	int ballShift = m_radius/4;

	// top point of the ball
	if ( checkPointInRect(top_x, top_y, go->getRect()) )
	{
		if(go->getID() == "paddle")
		{
			const float PI = 3.1415926535;

			float initialAngle = PI/4;	//	PI/6;
			float angleRange = initialAngle*2;	//	4 * initialAngle;

			// determines the angle that the ball will shoot off from the paddle
			// based on where it hit the paddle (near the edges, center, etc.)
			float angleNumerator = (go->getRect().x + go->getRect().w) - top_x;
			float angleDenominator = go->getRect().w;
			if(angleDenominator == 0) angleDenominator = 1;	// shouldn't EVER be 0 anyway...
			float percentAngleOfPaddle = angleNumerator/angleDenominator;
			float angle = initialAngle + (percentAngleOfPaddle * angleRange);

			// determines the speed that the ball will shoot off from the paddle
			// based on where it hit the paddle (near the edges, center, etc.)
			float speedNumerator = fabs((double)((go->getRect().x + go->getRect().w/2) - top_x));
			float speedDenominator = go->getRect().w/2;
			if(speedDenominator == 0) speedDenominator = 1;	// shouldn't EVER be 0 anyway...
			float percentSpeedOfPaddle = speedNumerator/speedDenominator;
			float speed = m_minSpeed + (percentSpeedOfPaddle * (m_maxSpeedDiff));

			setVel(Vector2D(angle)*(speed));
			setPos(getPos().x, getPos().y + ballShift);
		}
		else
		{
			setVel(getVel().x,-(getVel().y));
			setPos(getPos().x, getPos().y + ballShift);
		}
		returnVal = true;
	}
	// bottom point of the ball
	if ( checkPointInRect(bottom_x, bottom_y, go->getRect()) )
	{
		if(go->getID() == "paddle")
		{
			const float PI = 3.1415926535;

			float initialAngle = PI/4;	//	PI/6;
			float angleRange = initialAngle*2;	//	4 * initialAngle;

			// determines the angle that the ball will shoot off from the paddle
			// based on where it hit the paddle (near the edges, center, etc.)
			float angleNumerator = (go->getRect().x + go->getRect().w) - bottom_x;
			float angleDenominator = go->getRect().w;
			if(angleDenominator == 0) angleDenominator = 1;	// shouldn't EVER be 0 anyway...
			float percentAngleOfPaddle = angleNumerator/angleDenominator;
			float angle = initialAngle + (percentAngleOfPaddle * angleRange);

			// determines the speed that the ball will shoot off from the paddle
			// based on where it hit the paddle (near the edges, center, etc.)
			float speedNumerator = fabs((double)((go->getRect().x + go->getRect().w/2) - bottom_x));
			float speedDenominator = go->getRect().w/2;
			if(speedDenominator == 0) speedDenominator = 1;	// shouldn't EVER be 0 anyway...
			float percentSpeedOfPaddle = speedNumerator/speedDenominator;
			float speed = m_minSpeed + (percentSpeedOfPaddle * (m_maxSpeedDiff));

			setVel(Vector2D(angle)*(speed));
			// when hitting the 'TOP' part of a paddle
			// it will have to have an upward velocity,
			// which is in the negative y-direction
			setVel(getVel().x, -(getVel().y));
			setPos(getPos().x, getPos().y - ballShift);

			//std::cout << "numerator/denominator = " << speedNumerator <<"/"<< speedDenominator<<" = " << speedNumerator/speedDenominator << endl;
			//std::cout << "Vector: " << getVel() << "       percentSpeedOfPaddle: " << percentSpeedOfPaddle << endl;
		}
		else
		{
			setVel(getVel().x,-(getVel().y));
			setPos(getPos().x, getPos().y - ballShift);
		}
		returnVal = true;
	}
	// left point of the ball
	if ( checkPointInRect(left_x, left_y, go->getRect()) )
	{
		setVel(-(getVel().x),getVel().y);
		setPos(getPos().x + ballShift, getPos().y);
		returnVal = true;
	}
	// right point of the ball
	if ( checkPointInRect(right_x, right_y, go->getRect()) )
	{
		setVel(-(getVel().x),getVel().y);
		setPos(getPos().x - ballShift, getPos().y);
		returnVal = true;
	}

	return returnVal;
}

bool Object_Ball::checkPointInRect(int x, int y, SDL_Rect rect)
{
	if ( (x >= rect.x) && (x <= rect.x + rect.w) && 
		(y >= rect.y) && (y <= rect.y + rect.h) )
	{
		return true;
	}
	return false;
}

void Object_Ball::reset()
{
	setPos(m_startingPos);
	setVel(Vector2D(0,0));
	m_outOfBounds = false;
}