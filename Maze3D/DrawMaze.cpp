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

	for (int i = 0; i < heightOfMaze; i++) {
		std::cout << std::endl;
		for (int j = 0; j < widthOfMaze; j++) {
			std::cout << netOfMaze[i][j] << "|";
		}
	}

}

int DrawMaze::lenghtOfTheFile() {
	plik.seekg(0, plik.end);
	int lenght = plik.tellg();
	plik.seekg(0, plik.beg);

	return lenght;
}


void DrawMaze::wall(){
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, sizeOfOneCell, 0);
	glVertex3f(0, sizeOfOneCell, sizeOfOneCell);
	glVertex3f(0, 0, sizeOfOneCell);
	glEnd();

}

//szerokosc labiryntu to oœ z
//wysokosc labiryntu to os x

void DrawMaze::drawTheWall(bool whereIsWall[], int i, int  j) {
	if (whereIsWall[0]) {//gora
		glPushMatrix();
		glTranslatef(sizeOfOneCell*(i), 0, sizeOfOneCell*(j));
		glRotatef(90, 0, 1, 0);
		wall();
		glPopMatrix();
	}
	if (whereIsWall[1]) {//prawa
		glPushMatrix();
		glTranslatef(sizeOfOneCell*(i+1), 0, sizeOfOneCell*(j));
		wall();
		glPopMatrix();
	}
	if (whereIsWall[2]) {//dol
		glPushMatrix();
		glTranslatef(sizeOfOneCell*(i), 0, sizeOfOneCell*(j + 1));
		glRotatef(90, 0, 1, 0);
		wall();
		glPopMatrix();
	}
	if (whereIsWall[3]) {//lewa
		glPushMatrix();
		glTranslatef(sizeOfOneCell*(i), 0, sizeOfOneCell*(j));
		wall();
		glPopMatrix();
	}
}

bool DrawMaze::drawTheMaze(){

	if (heightOfMaze < 2 || widthOfMaze < 2) {
		std::cout << "Stworz wiekszy labirynt!" << std::endl;
		std::cin.get();
		exit(0);
	}


	glBegin(GL_QUADS); //podloga
		glColor3f(0, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1*widthOfMaze*sizeOfOneCell);
		glVertex3f(1*heightOfMaze*sizeOfOneCell, 0, 1*widthOfMaze*sizeOfOneCell);
		glVertex3f(1*heightOfMaze*sizeOfOneCell, 0, 0);
	glEnd();
		
	//glColor3f(0.3, 0.2, 0.2);
	//glTranslatef(sizeOfOneCell/2, sizeOfOneCell/2, sizeOfOneCell/2);



	
	//glPushMatrix();
	/*
	for (int i = 0; i < heightOfMaze; i++) {
		for (int j = 0; j < widthOfMaze; j++) {
			if (netOfMaze[i][j] == 'x') {
				glutSolidCube(sizeOfOneCell);
			}
			if (netOfMaze[i][j] == 's' && !isSetPos) {
				std::cout << "ustawienie punktu poczatkowego" << i << ":" << j << std::endl;
				move.setPos((i+1)*sizeOfOneCell+0.4, (j+1)*sizeOfOneCell+0.4);
				isSetPos = true;
			}
			glTranslatef(sizeOfOneCell, 0, 0);
		}
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0, 0, sizeOfOneCell*i);
	}
		*/

	for (int i = 0; i < heightOfMaze; i++) {
		for (int j = 0; j < widthOfMaze; j++) {
			if (netOfMaze[i][j] == 'o') {
				bool wall[] = {false,false,false,false };//gora, prawa, dol, lewa
				if (i == 0) {
					wall[3] = true;
					if (netOfMaze[i + 1][j] == 'x') { //zagwarantowane jest ze rozmiar labiryntu to co najmiej 2x2
						wall[1] = true;
					}
				}
				if (j == 0) {
					wall[0] = true;
					if (netOfMaze[i][j + 1] == 'x') {
						wall[2] = true;
					}
				}
				if (i == (heightOfMaze - 1)) {
					wall[1] = true;
					if (netOfMaze[i - 1][j] == 'x') {
						wall[3] = true;
					}
				}
				if (j == (widthOfMaze - 1)) {
					wall[2] = true;
					if (netOfMaze[i][j - 1] == 'x') {
						wall[0] = true;
					}
				}
				if (i > 0 ) {//lewo 
					if (netOfMaze[i - 1][j] == 'x') {
						wall[3] = true;
					}
				}
				if (i < (heightOfMaze - 1)) {//prawo
					if (netOfMaze[i + 1][j] == 'x') {
						wall[1] = true;
					}
				}
				if ( j<(widthOfMaze-1)) {//dol 
					if (netOfMaze[i][j + 1] == 'x') {
						wall[2] = true;
					}
				}
				if ( j > 0) {//gora
					if (netOfMaze[i][j - 1] == 'x') {
						wall[0] = true;
					}
				}

				drawTheWall(wall, i, j); //i idzie wzdluz osi x, a j wzdluz osi z
			}
		}
	}

	//glPopMatrix();

	return true;
}

DrawMaze::DrawMaze(Move& move){
	this->move = move;
	loadTheNetOfMaze();
}


DrawMaze::~DrawMaze(){

}
