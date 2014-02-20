#ifndef __LEVEL_LOADER_H__
#define	__LEVEL_LOADER_H__

#include <ostream>
#include <fstream>
#include <set>

#include "GameObject.h"

// can load the levels from .txt files
class LevelLoader
{
public:
	static std::set<GameObject*> Load(std::string levelFileName="levels\\level01.txt");

protected:
	LevelLoader() { }
	~LevelLoader() { }

private:
	static std::string		m_fileName;
	static std::ifstream	m_fileInput;
};

#endif	// __LEVEL_LOADER_H__