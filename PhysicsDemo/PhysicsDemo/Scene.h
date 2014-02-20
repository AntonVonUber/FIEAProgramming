#ifndef __SCENE_H__
#define __SCENE_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "glut.h"
#endif

#include "freeglut.h"
#include "freeglut_std.h"
#include "freeglut_ext.h"

#include <vector>
#include "SceneObject.h"

class Scene
{
private:
	// currently edited so only accepts HandObjects
	typedef std::vector<SceneObject*> ObjectList;

public:
	typedef ObjectList::size_type		ObjectsSizeType;
	typedef ObjectList::iterator		ObjectsIterator;
	typedef ObjectList::const_iterator	ConstObjectsIterator;

	Scene();
	~Scene();

	void					initialize();
	void					update(float deltaTime);

	void					render();
	void					renderGrid();

	//void					renderGUI();

	void					close();

	// if multiple objects link to Scene.h, must put the function body in Scene.cpp...
	ObjectsIterator			getFirstObject() { return m_objects.begin(); } ;
	ConstObjectsIterator	getFirstObject() const { return m_objects.begin(); };

	ObjectsIterator			getLastObject() { return m_objects.end(); };
	ConstObjectsIterator	getLastObject() const { return m_objects.end(); };
	
	void					pushObject(SceneObject* object) { m_objects.push_back(object); };
//	void					destroyObject(SceneObject* object) { m_objects. };	// rewrite this

private:
	ObjectList				m_objects;
	float					m_time;
};

inline Scene::Scene() { }
inline Scene::~Scene() { close(); }

#endif	// __SCENE_H__