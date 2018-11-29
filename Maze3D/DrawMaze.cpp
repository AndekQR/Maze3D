#include "DrawMaze.h"

std::ifstream plik("mazePattern.txt", std::ios::in);


char * DrawMaze::loadTheNetOfMaze(){
	if (!plik.good()){
		perror("B³¹d otwarcia pliku ze wzorem labiryntu!");
	}
	else {
		while (!plik.eof()) {
			plik >> charBufor;
			//std::cout << charBufor << std::endl;
			tabBufor.push_back(charBufor);
		}
	}
	for (int i = 0; i < tabBufor.size()-1; i++){
		std::cout << tabBufor[i]<< std::endl;

	}

	return nullptr;
}

int DrawMaze::lenghtOfTheFile() {
	plik.seekg(0, plik.end);
	int lenght = plik.tellg();
	plik.seekg(0, plik.beg);

	return lenght;
}

DrawMaze::DrawMaze(){
	loadTheNetOfMaze();
}


DrawMaze::~DrawMaze(){
}
