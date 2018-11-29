#include "Move.hpp"


void Move::setPos(float inXPos, float inZPos) {
	initXPos = inXPos;
	xPos = inXPos;
	initZPos = inZPos;
	zPos = inZPos;
}

void Move::reset() {
	xPos = initXPos;
	zPos = initZPos;
	angle = 0;
}

void Move::moveForward(bool move) {
	if (move) speed = 0.03f;
	else speed = 0;

}

void Move::moveBackward(bool move) {
	if (move)
		speed = -0.03f;
	else speed = 0;
}

void Move::turnLeft(bool move) {
	if (move)
		turn = 0.05f;
	else turn = 0;
}

void Move::turnRight(bool move) {
	if (move)
		turn = -0.05f;
	else turn = 0;
}


Move::Move()
{
}


Move::~Move()
{
}
