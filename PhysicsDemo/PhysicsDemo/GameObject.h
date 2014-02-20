#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include <string>
#include "Vector3.h"

// This is a virtual (abstract) class
// from which children inherit
class SceneObject
{
public:
	SceneObject() { };
	virtual			~SceneObject() { };
	friend	class	Scene;

	virtual void	init() = 0;
	virtual void	update() = 0;
	virtual	void	render() = 0;
	virtual void	close() = 0;

	// accessors
	inline	std::string		name() { return m_name; };
	inline	Vector3			position() { return m_position; };
	inline	Vector3			velocity() { return m_velocity; };
	inline	Vector3			momentum() { return m_momentum; };
	inline	long double		mass() { return m_mass; };
	inline	long double		kfriction() { return m_frictionK; };
	inline	long double		sFriction() { return m_frictionS; };
	// for individual components of position
	inline	long double		x() { return m_position.x(); };
	inline	long double		y() { return m_position.y(); };
	inline	long double		z() { return m_position.z(); }
	inline	long double		width() { return m_width; };
	inline	long double		r() { return m_red; };
	inline	long double		g() { return m_green; };
	inline	long double		b() { return m_blue; };


	// mutators
	inline	std::string		name(std::string name) { return (m_name = name); };
	inline	Vector3			position(Vector3 pos) { return (m_position = pos); };
	inline	Vector3			velocity(Vector3 vel) { return (m_velocity = vel); };
	inline	Vector3			momentum(Vector3 p) { return (m_momentum = p); };
	inline	long double		mass(double m) { return (m_mass = m); };
	inline	long double		kfriction(double k) { return (m_frictionK = k); };
	inline	long double		sFriction(double s) { return (m_frictionS = s); };
	inline	long double		x( double num ) { return (m_position.x(num)); }
	inline	long double		y( double num ) { return (m_position.y(num)); }
	inline	long double		z( double num ) { return (m_position.z(num)); }
	inline	long double		width( double num ) { return (m_width = num); }
	inline	long double		r( float num ) { return (m_red = num); };
	inline	long double		g( float num ) { return (m_green = num); };
	inline	long double		b( float num ) { return (m_blue = num); };


private:
	std::string		m_name;			// the name of the current object

	Vector3			m_position;		// the current position in 3D (or 2D) space
	Vector3			m_velocity;		// this is the speed/rate of change in position
	long double		m_mass;			// this is the simulated mass of the object
	Vector3			m_momentum;		// this is approx. mass x current-velocity

	long double		m_height;
	long double		m_width;
	long double		m_depth;			// in case needed...

	float			m_frictionK;	// sliding friction force
	float			m_frictionS;	// static friction force

	float			m_red;
	float			m_green;
	float			m_blue;
};

#endif	// __SCENE_OBJECT_H__