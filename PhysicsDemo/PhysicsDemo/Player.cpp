#include "Player.h"

void Player::init()
{
	name("Spaceship");
	position(Vector3(-10.0f,0.0f,0.0f));// position(Vector3(-7e6,0,0));//-10*3.2e6, 0, 0));
	velocity(Vector3(0.0f,1.0f,1.0f));	// velocity(Vector3(0, 2e3, 0));
	mass(15.0f);					// mass(15e3);
	Vector3 temp = velocity();
	momentum(temp.scalarMult(mass()));	// momentum(velocity().scalarMult(mass()));
	width(2.0f);					// width(2e6);
	kfriction(0.0f);
	sFriction(0.0f);
	r(1.0f);
	g(1.0f);
	b(0.0f);
}
void Player::init(std::string n, Vector3 pos, Vector3 vel,
		long double m, long double w,
		long double kF, long double sF,
		float red, float green, float blue)
{
	name(n);
	position(pos);
	velocity(vel);
	mass(m);
	Vector3 temp = velocity();
	momentum(temp.scalarMult(mass()));
	width(w);
	kfriction(kF);
	sFriction(sF);
	r(red);
	g(green);
	b(blue);
}


void Player::update()
{
	// add code to update forces-applied/velocity/position, etc.
}


void Player::render()
{
	glColor3f(r(), g(), b());
	glTranslatef(position().x(), position().y(), position().z());
	glutSolidSphere(width()/2,100,100);
}


void Player::close()
{
	// if need be, a function to free
	// dynamically allocated data
}