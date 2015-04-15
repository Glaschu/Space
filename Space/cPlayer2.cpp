/*
=================
cPlayer2.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cPlayer2.h"

void cPlayer2::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cPlayer2::update(float deltaTime)
{
	
	//keyboard enter to move
	if (m_InputMgr->isKeyDown('D'))
	{
		spritePos2D.x += 10.0f;
	}
	if (m_InputMgr->isKeyDown('A'))
	{
		spritePos2D.x -= 10.0f;

	}
	if (m_InputMgr->isKeyDown('S'))
	{
		
		if (theSpaceBullets.size() - 1 !=3 ){
			// Add new bullet sprite to the vector array
			theSpaceBullets.push_back(new cBullet2);
			int numBullets = theSpaceBullets.size() - 1;
			theSpaceBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
			theSpaceBullets[numBullets]->setSpriteTranslation(glm::vec2(-2.0f, -2.0f));
			theSpaceBullets[numBullets]->setTexture(theGameTextures[5]->getTexture());
			theSpaceBullets[numBullets]->setTextureDimensions(theGameTextures[5]->getTWidth(), theGameTextures[5]->getTHeight());
			theSpaceBullets[numBullets]->setSpriteCentre();
			theSpaceBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
			theSpaceBullets[numBullets]->setSpriteRotation(getSpriteRotation());
			theSpaceBullets[numBullets]->setActive(true);
			theSpaceBullets[numBullets]->setMdlRadius();
			//play the firing sound
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		}
 

	}
	//makes sure the player cant go off screen
	if (spritePos2D.x + (textureWidth / 2) > 1754){
		spritePos2D.x -= 5.0f;
		
	}
	if (spritePos2D.x - (textureWidth / 2) < 0){
		spritePos2D.x += 5.0f;

	}



	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}


	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet2*>::iterator bulletIterartor = theSpaceBullets.begin(); bulletIterartor != theSpaceBullets.end(); ++bulletIterartor)
	{
		
		
		(*bulletIterartor)->update(deltaTime);
	
		for (vector<cAiPlayer*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				Score2 += 10;
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
			}
		}


	}
	//for when the player is hit by bullet -1 lives
	for (vector<cBullet*>::iterator p2Bullets = theRocketBullets.begin(); p2Bullets != theRocketBullets.end(); ++p2Bullets){
		(*p2Bullets)->update(deltaTime);
		if ((*p2Bullets)->getSpritePos().x > spritePos2D.x - (textureWidth / 2) && (*p2Bullets)->getSpritePos().x<spritePos2D.x + (textureWidth / 2) && (*p2Bullets)->getSpritePos().y>spritePos2D.y - (textureHeight / 2) && (*p2Bullets)->getSpritePos().y < spritePos2D.y + (textureHeight / 2)){
			life -= 1;
			(*p2Bullets)->setActive(false);
		}
	}

	vector<cBullet2*>::iterator bulletIterartor = theSpaceBullets.begin();
	while (bulletIterartor != theSpaceBullets.end())
	{
		//play sound and erase bullet
		if ((*bulletIterartor)->isActive() == false)
		{
			
			bulletIterartor = theSpaceBullets.erase(bulletIterartor);
			 //play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		//detroy bullet after leaves the screen
		else if ((*bulletIterartor)->getSpritePos().y > 1000){
			bulletIterartor = theSpaceBullets.erase(bulletIterartor);
		}
		else
		{
			(*bulletIterartor)->update(deltaTime);
			(*bulletIterartor)->render();
			++bulletIterartor;
		}
	}
}
/*
=================================================================
Sets the velocity for the rocket
=================================================================
*/
void cPlayer2::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
Gets the rocket velocity
=================================================================
*/
glm::vec2 cPlayer2::getRocketVelocity()
{
	return rocketVelocity;
}
int cPlayer2::getScore(){
	return Score2;
}
//resets the lives ,bullets and score
void cPlayer2::setLives(bool lives){
	if (lives){
		life = 3;
		Score2 = 0;
		vector<cBullet2*>::iterator bulletIterartor = theSpaceBullets.begin();
		while (bulletIterartor != theSpaceBullets.end()){
			bulletIterartor = theSpaceBullets.erase(bulletIterartor);
		}
	}
}
//send the players score and life
string cPlayer2::getInfo()
{
	stringstream output;
	output << "Score: " << Score2 << "    Life: " << life;
	return output.str();
}
//send if the player is dead
bool cPlayer2::getDeath(){
	if (life <= 0){
		return true;
	}
	else{
		return false;
	}
}
