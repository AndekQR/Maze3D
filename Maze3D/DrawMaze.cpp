#include "DrawMaze.h"

std::ifstream plik("mazePattern.txt", std::ios::in);


void DrawMaze::loadTheNetOfMaze(){
	if (!plik.good()){ //sprawdz czy plik jest otwarty
		perror("B³¹d otwarcia pliku ze wzorem labiryntu!");
	}
	else {
		while (!plik.eof()) { //pobranie danych do bufora
			plik >> charBufor; //pobranie jednego znaku z pliku
			tabBufor.push_back(charBufor); //i wpisanie go do vectora
		}
	}

	int numberOfData = 0;
	int multiplier = 1;
	for (int i = tabBufor.size()-1; i >=0; i--){ //wczytnaie szerokoci, wysokosci i poczatku wzoru labiryntu
		if (tabBufor[i] == ';') {
			numberOfData++;
			if (numberOfData == 1) {
				startingPositionOfTheMaze = i;
				startingPositionOfTheMaze++; //bo obecnie jest na ';'
			}
			multiplier = 1;
			continue;
		}
		if (numberOfData == 2) {
			heightOfMaze = heightOfMaze + ((int)tabBufor[i] - 48) * multiplier;
			multiplier = multiplier * 10;
		}
			
		if (numberOfData == 1) {
			widthOfMaze = widthOfMaze + ((int)tabBufor[i] - 48)*multiplier;
			multiplier = multiplier * 10;
		}

	}
	
	netOfMaze = new char*[heightOfMaze];
	for (int i = 0; i < heightOfMaze; i++) {
		netOfMaze[i] = new char[widthOfMaze];
	}

	int licznik = startingPositionOfTheMaze;
	for (int i = 0; i < heightOfMaze; i++) {
		for (int j = 0; j < widthOfMaze; j++) {
			netOfMaze[i][j] = tabBufor[licznik];
			licznik++;
		}
	}

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
