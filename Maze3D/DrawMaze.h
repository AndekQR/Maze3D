#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class DrawMaze
{

private:
	char** netOfMaze; //dwuwymiarowa dynamiczna tablica charow 
	std::vector<char> tabBufor;
	char charBufor;
	int widthOfMaze, heightOfMaze, sizeOfOneCell;
	char* loadTheNetOfMaze();
	int lenghtOfTheFile();
public:
	DrawMaze();
	~DrawMaze();
};


