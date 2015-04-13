#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"

#include "asteroidsGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
	const int windowWidth = 1754;//1754	
	const int windowHeight = 1000;//1000
    const int windowBPP = 64;



    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
    windowOGL theOGLWnd;
	
    //Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\AiPlayer.png", "Images\\asteroid2.png", "Images\\asteroid3.png", "Images\\asteroid4.png", "Images\\Player1Bullet.png","Images\\Player2Bullet.png" };
	for (int tCount = 0; tCount < 6; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	// Create vector array of textures
	float AiStartX = 100;
	float AiStartY = 300;
	for (int astro = 0; astro < 40; astro++)
	{
		theAsteroids.push_back(new cAsteroid);
		theAsteroids[astro]->setSpritePos(glm::vec2(AiStartX, AiStartY));
		//theAsteroids[astro]->setSpriteTranslation(glm::vec2((rand() % 4 + 1), (rand() % 4 + 1)));
		//int randAsteroid = rand() % 4;
		theAsteroids[astro]->setTexture(theGameTextures[0]->getTexture());
		theAsteroids[astro]->setTextureDimensions(theGameTextures[0]->getTWidth(), theGameTextures[0]->getTHeight());
		theAsteroids[astro]->setSpriteCentre();
		theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theAsteroids[astro]->setActive(true);
		theAsteroids[astro]->setMdlRadius();
		AiStartX += 130;
		if (astro == 9){
			AiStartY += 100;
			AiStartX = 100;
		}
		if (astro == 19){
			AiStartY += 100;
			AiStartX = 100;
		}	if (astro == 29){
			AiStartY += 100;
			AiStartX = 100;
		}
		
	}


	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\SpaceBack.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\Player1.png");
	cRocket rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(800.0f, 900.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
	
	cTexture player2txt;
	player2txt.createTexture("Images\\Player2.png");
	cPlayer2 player2Sprite;
	player2Sprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	player2Sprite.setSpritePos(glm::vec2(500.0f, 100.0f));
	player2Sprite.setTexture(player2txt.getTexture());
	player2Sprite.setTextureDimensions(player2txt.getTWidth(), player2txt.getTHeight());
	player2Sprite.setSpriteCentre();
	player2Sprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));

//	rocketSprite.player2R(player2Sprite);
	//player2R(player2Sprite);

	// Attach sound manager to rocket sprite
	rocketSprite.attachSoundMgr(theSoundMgr);

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		spriteBkgd.render();

		rocketSprite.update(elapsedTime);
		player2Sprite.update(elapsedTime);
		vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin();
		while (asteroidIterator != theAsteroids.end())
		{
			if ((*asteroidIterator)->isActive() == false)
			{
				asteroidIterator = theAsteroids.erase(asteroidIterator);
			}
			else
			{
				(*asteroidIterator)->update(elapsedTime);
				(*asteroidIterator)->render();
				++asteroidIterator;
			}

			
		}
		

		rocketSprite.render();
		player2Sprite.render();
		int scoreP1 = rocketSprite.getScore();
		int scoreP2 = player2Sprite.getScore();
		string player1Dis = "Score " + scoreP1;
		theFontMgr->getFont("Space")->printText("Space Invaders", FTPoint(0.0f, 1.0f, 0.0f));
		theFontMgr->getFont("Space")->printScore(rocketSprite.getInfo().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
	
		

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
