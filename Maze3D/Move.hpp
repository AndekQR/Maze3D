#pragma once
class Move
{
public:
	float xPos=1 , initXPos, xLookAt = 0;
	float zPos=1 , initZPos, zLookAt = 0;
	float speed = 0;
	float angle = 0;
	float turn = 0;

	void setPos(float inXPos, float inZPos);
	void reset();
	void moveForward(bool move);
	void moveBackward(bool move);
	void turnLeft(bool move);
	void turnRight(bool move);

	Move();
	~Move();
};


