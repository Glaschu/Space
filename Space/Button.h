/*
=================
Palyer2.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
=================
*/

#ifndef _BUTTON_H
#define _BUTTON_H
#include "cSprite.h"
#include "SpaceInvader.h"


class Button :  public cSprite
{
private:
	

bool pressed;

public:
	
	Button();

	void update(float deltaTime);//check presssed
	bool getPressed();//return press
	void setPressed(bool value);//set pressed

};
#endif


