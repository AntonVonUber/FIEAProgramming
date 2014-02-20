#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "glut.h"
#include "Vector3.h"
#include "SceneObject.h"

// The player-controlled
// object in the scene
class Player : public SceneObject
{
public:
	Player() { };
	Player(std::string n, Vector3 pos, Vector3 vel,
		long double m, long double w,
		long double kF, long double sF,
		float r, float g, float b)
	{ init(n, pos, vel, m, w, kF, sF, r, g, b); };
	Player(std::string n, Vector3 pos) { init(); name(n); position(pos); };
	virtual ~Player() { };
//	friend	class	Scene;
	friend class GravityOrb;

	void init();
	void init(std::string n, Vector3 pos, Vector3 vel,
		long double mass, long double width,
		long double kF, long double sF,
		float r, float g, float b);
	void update();
	void render();
	void close();
};

#endif	// __PLAYER_H__