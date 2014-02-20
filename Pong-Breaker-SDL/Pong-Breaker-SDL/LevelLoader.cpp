#include "LevelLoader.h"
#include "Object_Brick.h"
#include "Object_Ball.h"
#include "Object_Paddle.h"
#include "Window.h"

std::string LevelLoader::m_fileName;
std::ifstream LevelLoader::m_fileInput;

std::set<GameObject*> LevelLoader::Load(std::string levelFileName)
{
	int numRows = 13, numCols = 10;
	std::set<GameObject*> objects;
	m_fileInput.open(levelFileName, fstream::in);

	int initialX = (int)(Window::Box().w * 0.05);
	int initialY = (int)(Window::Box().h * 0.07);

	int xOffset = (int)(Window::Box().w * 0.1);
	int yOffset = (int)(Window::Box().w * 0.05);

	std::string ch, blockString;

	for(int i = 0; i < numRows; ++i)
	{
		for(int j = 0; j < numCols; ++j)
		{
			m_fileInput >> ch;
			if(ch == "5")
			{
				Object_Brick* temp = new Object_Brick(Vector2D(initialX + (j*xOffset),
					initialY + (i*yOffset)), "images\\brick_darkgrey.png", atoi(ch.c_str()));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "4")
			{
				Object_Brick* temp = new Object_Brick(Vector2D(initialX + (j*xOffset),
					initialY + (i*yOffset)), "images\\brick_blue.png", atoi(ch.c_str()));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "3")
			{
				Object_Brick* temp = new Object_Brick(Vector2D(initialX + (j*xOffset),
					initialY + (i*yOffset)), "images\\brick_red.png", atoi(ch.c_str()));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "2")
			{
				Object_Brick* temp = new Object_Brick(Vector2D(initialX + (j*xOffset),
					initialY + (i*yOffset)), "images\\brick_orange.png", atoi(ch.c_str()));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "1")
			{
				Object_Brick* temp = new Object_Brick(Vector2D(initialX + (j*xOffset),
					initialY + (i*yOffset)), "images\\brick_yellow.png", atoi(ch.c_str()));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "b")
			{
				Object_Ball* temp = new Object_Ball(Vector2D(initialX + (j*xOffset), initialY + (i*yOffset)));
				temp->Init();
				objects.insert(temp);
			}
			if(ch == "p")
			{
				Object_Paddle* temp = new Object_Paddle(Vector2D(initialX + (j*xOffset), initialY + (i*yOffset)));
				temp->Init();
				objects.insert(temp);
			}
		}
	}
	m_fileInput.close();

	return objects;
}