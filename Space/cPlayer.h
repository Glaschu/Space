/*
=================
cPlayer.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/
#ifndef _cPLAYER_H
#define _cPLAYER_H

#include "cSprite.h"
#include "cPlayer2.h"
#include <iostream>
#include <sstream>
#include "SpaceInvader.h"
using namespace std;

class cPlayer : public cSprite
{
private:
	glm::vec2 rocketVelocity = glm::vec2(0.0f, 0.0f);
	int life = 3;
	int once = 1;

public:
	string getInfo();
	int Score;
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setRocketVelocity(glm::vec2 rocketVel);   // Sets the velocity for the rocket
	glm::vec2 getRocketVelocity();				 // Gets the rocket velocity
	int cPlayer::getScore();//get player score
	bool getDeath();//get player death
	void setLives(bool lives);//resets the lives
};
#endif