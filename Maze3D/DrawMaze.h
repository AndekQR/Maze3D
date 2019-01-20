#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Move.hpp"
#include "TextureManager.h"

class DrawMaze
{

private:
	Move* move = NULL;
	TextureManager* textureManager = NULL;
	int startingPositionOfTheMaze=0; //pozycja od ktorej w buforze zaczyna sie labirynt
	char** netOfMaze; //wzór na podstawie ktorego jest rysowany labirynt  x-rysuj blok, o-nie rysuj, s-punkt startowy, e-punkt koncowy
	std::vector<char> tabBufor;
	char charBufor;
	int widthOfMaze = 0, heightOfMaze = 0;
	GLfloat sizeOfOneCell = 2.0f;
	void loadTheNetOfMaze();
	int lenghtOfTheFile();
	bool isSetPos = false;
	void wall();
	void drawTheWall(bool wall[], int i, int j);
	void floor(int y, int x);
	
	GLuint* tex;
public:
	bool drawTheMaze();
	DrawMaze(Move*& moveP, TextureManager* textureManager, GLuint* tex);
	~DrawMaze();
};


