#include "GravityOrb.h"

void GravityOrb::init()
{
	name("Earth");
	position(Vector3());	// position(Vector3());
	velocity(Vector3());	// velocity(Vector3());
	mass(60.0f);			// mass(6e24);
	Vector3 temp = velocity();
	momentum(temp.scalarMult(mass()));	// momentum(Vector3());
	width(12.8f);			// width(12.8e6/100);
	kfriction(0.0f);
	sFriction(0.0f);
	r(0.0f);
	g(0.0f);
	b(1.0f);
}
void GravityOrb::init(std::string n, Vector3 pos, Vector3 vel,
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


void GravityOrb::update()
{
	// add code to update forces-applied/velocity/position, etc.
}


void GravityOrb::render()
{
	glColor3f(r(), g(), b());
	glTranslatef(position().x(), position().y(), position().z());
	glutSolidSphere(width()/2, 100, 100);
}


void GravityOrb::close()
{
	// if need be, a function to free
	// dynamically allocated data
}