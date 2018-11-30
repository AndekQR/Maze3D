#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class DrawMaze
{

private:
	int startingPositionOfTheMaze=0; //pozycja od ktorej w buforze zaczyna sie labirynt
	char** netOfMaze; //dwuwymiarowa dynamiczna tablica charow 
	std::vector<char> tabBufor;
	char charBufor;
	int widthOfMaze=0, heightOfMaze=0, sizeOfOneCell;
	void loadTheNetOfMaze();
	int lenghtOfTheFile();
public:
	DrawMaze();
	~DrawMaze();
};


