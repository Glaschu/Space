/*
=================
Palyer2.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _CPLAYER2_H
#define _CPLAYER2_H
#include "cSprite.h"
#include "SpaceInvader.h"
#include "cBullet2.h"

class cPlayer2 : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);
	int Score2;
	int life = 3;
	int once = 1;


public:
	string getInfo();
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	glm::vec2 getRocketVelocity();				 // Gets the rocket velocity
	int cPlayer2::getScore();//get player score
	bool getDeath();//get player death
	void setLives(bool lives);//resets the lives
};
#endif