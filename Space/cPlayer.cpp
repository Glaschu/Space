/*
=================
cPlayer.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/

#include "cPlayer.h"
using namespace std;
/*void cPlayer::player2R(cPlayer2 p2){
	player2 = p2;
}*/
void cPlayer::render()
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

void cPlayer::update(float deltaTime)
{
	
	//keyboard enter to move
	
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 10.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 10.0f;
		
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		//no more the 4 bullets
		if (theRocketBullets.size() - 1 != 3){
			// Add new bullet sprite to the vector array
			theRocketBullets.push_back(new cBullet);
			int numBullets = theRocketBullets.size() - 1;
			theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
			theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(2.0f, 2.0f));
			theRocketBullets[numBullets]->setTexture(theGameTextures[4]->getTexture());
			theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
			theRocketBullets[numBullets]->setSpriteCentre();
			theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
			theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
			theRocketBullets[numBullets]->setActive(true);
			theRocketBullets[numBullets]->setMdlRadius();
			// play the firing sound
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
	for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
	{
		
		
	
		(*bulletIterartor)->update(deltaTime);
		for (vector<cAiPlayer*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				Score += 10;
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
			}
			
		}
		
	
		
		
	}//for when the player is hit by bullet -1 lives
	for (vector<cBullet2*>::iterator p2Bullets = theSpaceBullets.begin(); p2Bullets != theSpaceBullets.end(); ++p2Bullets){
		(*p2Bullets)->update(deltaTime);
		if ((*p2Bullets)->getSpritePos().x > spritePos2D.x - (textureWidth / 2) && (*p2Bullets)->getSpritePos().x<spritePos2D.x + (textureWidth / 2) && (*p2Bullets)->getSpritePos().y>spritePos2D.y - (textureHeight / 2) && (*p2Bullets)->getSpritePos().y < spritePos2D.y + (textureHeight / 2)){
			life -= 1;
			(*p2Bullets)->setActive(false);
		}
	}
	

	vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
	while (bulletIterartor != theRocketBullets.end())
	{//play sound and erase bullet
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}//detroy bullet after leaves the screen
		else if ((*bulletIterartor)->getSpritePos().y<0){
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
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
void cPlayer::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cPlayer::getRocketVelocity()
{
	return rocketVelocity;
}
int cPlayer::getScore(){
	return Score;
}//send the players score and life
string cPlayer::getInfo()
{
	stringstream output;
	output << "Score: " << Score<<"   Life: "<<life;
	return output.str();
}//resets the lives ,bullets and score
bool cPlayer::getDeath(){
	if (life <= 0){
		return true;
	}
	else{
		return false;
	}
}//send if the player is dead
void cPlayer::setLives(bool lives){
	if (lives){
		life = 3;
		Score = 0;
		once = 0;
		vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
		while (bulletIterartor != theRocketBullets.end()){
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
		}
	}
}

	
