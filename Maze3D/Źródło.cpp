#include <stdlib.h>
#include <gl/glut.h>
#include <math.h>
#include "ród³o.h"

#define ASPECT_1_1 1

float xPos = 1, initXPos, xLookAt = 0;
float zPos = 1, initZPos, zLookAt = 0;
float speed = 0;
float angle = 0;
float turn = 0;

void display() {

	angle = angle + turn;

	//Update the camera position based on the current camera speeds
	xPos = xPos + speed * sin(angle);
	zPos = zPos + speed * cos(angle);

	//update the look-at position based on the current cam position
	xLookAt = (float)(xPos + sin(angle));
	zLookAt = (float)(zPos + cos(angle));

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie buforu koloru i z-buforu
	
	glClearColor(1.0, 1.0, 1.0, 1.0); //bialy
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(xPos, 0, zPos, xLookAt, 0, zLookAt, 0, 1, 0);

	// kolor krawêdzi szeœcianu
	glColor3f(0.0, 0.0, 0.0);

	glutWireCube(10);

	

	glFlush();
	glutSwapBuffers();

}

void reshape(int width, int height) {
	/*
	glViewport(0, 0, width, height); //obszar renderingu ca³e okno

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (ASPECT_1_1 == 1) { //parametry bry³y obcinania
		if (width >= height && height>0) {
			glFrustum(-2.0 * width / height, 2.0 * width / height, -2.0, 2.0, 1.0, 5.0);
		}
		else {
			if (height > width && width>0) {
				glFrustum(-2.0, 2.0, -2.0 * height / width, 2.0 * height / width, 1.0, 5.0);
			}
		}
	}
	else {
		glFrustum(-2.0, 2.0, -2.0, 2.0, 1.0, 5.0);
	}

	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 0.01, 100);
	

	display();
}

void setPos(float inXPos, float inZPos) {
	initXPos = inXPos;
	xPos = inXPos;
	initZPos = inZPos;
	zPos = inZPos;
}

void reset() {
	xPos = initXPos;
	zPos = initZPos;
	angle = 0;
}

void moveForward(bool move) {
	if (move) speed = 0.03f;
	else speed = 0;

}

void moveBackward(bool move) {
	if (move)
		speed = -0.03f;
	else speed = 0;
}

void turnLeft(bool move) {
	if (move)
		turn = 0.05f;
	else turn = 0;
}

void turnRight(bool move) {
	if (move)
		turn = -0.05f;
	else turn = 0;
}




void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 0x1b:
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
		moveForward(true);
		display();
		break;
	case GLUT_KEY_DOWN:
		moveBackward(true);
		display();
		break;
	case GLUT_KEY_LEFT:
		turnLeft(true);
		display();
		break;
	case GLUT_KEY_RIGHT:
		turnRight(true);
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
		moveForward(false);
		break;
	case GLUT_KEY_DOWN:
		moveBackward(false);
		break;
	case GLUT_KEY_LEFT:
		turnLeft(false);
		break;
	case GLUT_KEY_RIGHT:
		turnRight(false);
		break;
	default:
		break;
	}
}

void mouseMotion(int x, int y) {

}

void mouseButton(int button, int state, int x, int y) {

}





int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); //podwojne buforowanie, ostatni parametr do z-bufora
	glutInitWindowSize(400, 400);
	glutCreateWindow("Maze3D");
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton); //obsluga przyciskow myszy
	glutMotionFunc(mouseMotion); //obsluga ruchu myszki
	glutSpecialFunc(specialKeys); //strzalki
	glutSpecialUpFunc(specialUpKeys);//obsluga puszczenia klawiszy 

	glEnable(GL_DEPTH_TEST);//wlaczenie bufora z
	setPos(1, 1);

	glutMainLoop();

	return(0);
}
