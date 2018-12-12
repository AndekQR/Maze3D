#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "Move.hpp"

class DrawMaze
{

private:
	Move* move = NULL;
	int startingPositionOfTheMaze=0; //pozycja od ktorej w buforze zaczyna sie labirynt
	char** netOfMaze; //wzór na podstawie ktorego jest rysowany labirynt  x-rysuj blok, o-nie rysuj, s-punkt startowy, e-punkt koncowy
	std::vector<char> tabBufor;
	char charBufor;
	int widthOfMaze = 0, heightOfMaze = 0;
	GLfloat sizeOfOneCell = 1.0f;
	void loadTheNetOfMaze();
	int lenghtOfTheFile();
	bool isSetPos = false;
	void wall();
	void drawTheWall(bool wall[], int i, int j);
	void floor(int x, int y);
public:
	bool drawTheMaze();

	DrawMaze(Move*& moveP);
	~DrawMaze();
};


