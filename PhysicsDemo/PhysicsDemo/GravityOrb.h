#ifndef __GRAVITY_ORB_H__
#define __GRAVITY_ORB_H__

#include "glut.h"
#include "Vector3.h"
#include "SceneObject.h"

// An object that is massive and thus
// exerts great gravitational force
class GravityOrb : public SceneObject
{
public:
	GravityOrb() { };
	GravityOrb(std::string n, Vector3 pos, Vector3 vel,
		long double m, long double w,
		long double kF, long double sF,
		float r, float g, float b)
	{ init(n, pos, vel, m, w, kF, sF, r, g, b); }
	GravityOrb(std::string n, Vector3 pos) { init(); name(n); position(pos); };	// doesn't need separate 'init()'
	virtual ~GravityOrb() { };
//	friend	class	Scene;
	friend class Player;

	void init();
	void init(std::string n, Vector3 pos, Vector3 vel,
		long double mass, long double width,
		long double kF, long double sF,
		float r, float g, float b);
	void update();
	void render();
	void close();
};

#endif	// __GRAVITY_ORB_H__