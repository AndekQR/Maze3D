#include <gl/glut.h>
#include <math.h>
#include "Move.hpp"
#include "DrawMaze.h"
#include <stdio.h>
#include "TextureManager.h"

#define ASPECT_1_1 1
#define FPS 50

Move* move = new Move;
DrawMaze* maze;
bool isMazeIsDrawn = false;

/* Parametry œwiat³a i materia³ów */
GLfloat lightAmb[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat lightDif[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat lightPos[] = { 100, 200, 0.0, 1.0 };
GLfloat lightSpec[] = { 1, 1, 1, 1 };


TextureManager* textureManager;
GLuint tex[2];

void display() {



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu koloru i z-buforu
	
	glClearColor(1.0, 1.0, 1.0, 1.0); //bialy - niebo
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(move->xPos, 0.5, move->zPos, move->xLookAt, 0.5, move->zLookAt, 0, 1, 0);
	//gluLookAt(move->xPos, 4, move->zPos, move->xLookAt, 3.7, move->zLookAt, 0, 1, 0); //widok z gory


	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	
	maze->drawTheMaze();


	glutSwapBuffers();

}

void reshape(int width, int height) {

	if (height == 0)	height = 1;
	
	glViewport(0, 0, width, height);

	/* Ustawienie obszaru obcinania z uwzglêdnieniem proporcji okna */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* Rzutowanie perspektywiczne */
	gluPerspective(50, (float)width / height, 0.01, 470);

	glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 0x1b:
		delete move;
		exit(0);
		break;
	default:
		break;
	}
}

void specialKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move->moveForward(true);
		display();
		break;
	case GLUT_KEY_DOWN:
		move->moveBackward(true);
		display();
		break;
	case GLUT_KEY_LEFT:
		move->turnLeft(true);
		display();
		break;
	case GLUT_KEY_RIGHT:
		move->turnRight(true);
		display();
		break;
	default:
		break;
	}
}

void specialUpKeys(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_UP:
		move->moveForward(false);
		break;
	case GLUT_KEY_DOWN:
		move->moveBackward(false);
		break;
	case GLUT_KEY_LEFT:
		move->turnLeft(false);
		break;
	case GLUT_KEY_RIGHT:
		move->turnRight(false);
		break;
	default:
		break;
	}
}

void timer(int val) {
	move->angle = move->angle + move->turn;

	//aktualizacja pozycji kamery na podstawie prêdkoœci kamery
	move->xPos = move->xPos + move->speed * sin(move->angle);
	move->zPos = move->zPos + move->speed * cos(move->angle);

	//aktualizacja kierunku patrzenia kamery na podstawie jej pozycji
	move->xLookAt = (float)(move->xPos + sin(move->angle));
	move->zLookAt = (float)(move->zPos + cos(move->angle));

	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer, 0);
}

void mouseMotion(int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {

}

void light() {
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);

	glEnable(GL_LIGHT0);

	glMaterialfv(GL_FRONT, GL_SPECULAR, lightSpec);
	glMateriali(GL_FRONT, GL_SHININESS, 64);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);


}


int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //podwojne buforowanie, ostatni parametr do z-bufora
	
	glutInitWindowSize(600, 600);
	glutCreateWindow("Maze3D");
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton); //obsluga przyciskow myszy
	glutMotionFunc(mouseMotion); //obsluga ruchu myszki
	glutSpecialFunc(specialKeys); //strzalki
	glutSpecialUpFunc(specialUpKeys);//obsluga puszczenia klawiszy 
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);//wlaczenie bufora z
	light();

	textureManager = TextureManager::Inst();
	glGenTextures(2, tex);
	textureManager->LoadTexture("floor.png", tex[0]);
	textureManager->LoadTexture("wall.jpg", tex[1]);

	maze = new DrawMaze(move, textureManager, tex);

	
	glutTimerFunc(1000 / FPS, timer, 0); //timer




	

	glutMainLoop();

	return(0);
}
