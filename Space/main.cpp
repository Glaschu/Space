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
#include "Button.h"
#include "SpaceInvader.h"
#include "MMsystem.h"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
	const int windowWidth = 1754;//1754	
	const int windowHeight = 1000;//1000
    const int windowBPP = 16;



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
	LPCSTR gameSounds[5] = { "Audio/lazer.wav", "Audio/click.wav", "Audio/exp.wav", "Audio/BackGround.wav", "Audio/tap.wav" };

	theSoundMgr->add("Shot", gameSounds[0]);
	theSoundMgr->add("Click", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);
	theSoundMgr->add("Theme", gameSounds[3]);
	theSoundMgr->add("Tap", gameSounds[4]);
	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/NewSpace.TTF" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	cTexture StartBkgd;
	StartBkgd.createTexture("Images\\StartSrn.png");
	cBkGround StartspriteBkgd;
	StartspriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	StartspriteBkgd.setTexture(StartBkgd.getTexture());
	StartspriteBkgd.setTextureDimensions(StartBkgd.getTWidth(), StartBkgd.getTHeight());
	
	cTexture HowBkgd;
	HowBkgd.createTexture("Images\\HowToSrn.png");
	cBkGround HowTospriteBkgd;
	HowTospriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	HowTospriteBkgd.setTexture(HowBkgd.getTexture());
	HowTospriteBkgd.setTextureDimensions(HowBkgd.getTWidth(), HowBkgd.getTHeight());

	cTexture playTxt;
	playTxt.createTexture("Images\\PlayBtn.png");
	Button PlaySprite;
	PlaySprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	PlaySprite.setSpritePos(glm::vec2(1000.0f, 900.0f));
	PlaySprite.setTexture(playTxt.getTexture());
	PlaySprite.setTextureDimensions(playTxt.getTWidth(), playTxt.getTHeight());
	PlaySprite.attachSoundMgr(theSoundMgr);// Attach sound manager to button sprite
	
	cTexture QuitTxt;
	QuitTxt.createTexture("Images\\QuitBtn.png");
	Button QuitSprite;
	QuitSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	QuitSprite.setSpritePos(glm::vec2(700.0f, 900.0f));
	QuitSprite.setTexture(QuitTxt.getTexture());
	QuitSprite.setTextureDimensions(QuitTxt.getTWidth(), QuitTxt.getTHeight());
	QuitSprite.attachSoundMgr(theSoundMgr);// Attach sound manager to button sprite
	cTexture HowTxt;
	HowTxt.createTexture("Images\\HowBtn.png");
	Button HowSprite;
	HowSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	HowSprite.setSpritePos(glm::vec2(400.0f, 900.0f));
	HowSprite.setTexture(HowTxt.getTexture());
	HowSprite.setTextureDimensions(HowTxt.getTWidth(), HowTxt.getTHeight());
	HowSprite.attachSoundMgr(theSoundMgr);// Attach sound manager to button sprite
	cTexture HomeTxt;
	HomeTxt.createTexture("Images\\HomeBtn.png");
	Button HomeSprite;
	HomeSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	HomeSprite.setSpritePos(glm::vec2(1300.0f, 900.0f));
	HomeSprite.setTexture(HomeTxt.getTexture());
	HomeSprite.setTextureDimensions(HomeTxt.getTWidth(), HomeTxt.getTHeight());
	HomeSprite.attachSoundMgr(theSoundMgr);// Attach sound manager to button sprite

	cTexture textureBkgd;
	textureBkgd.createTexture("Images\\SpaceBack.png");
	cBkGround spriteBkgd;
	spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
	spriteBkgd.setTexture(textureBkgd.getTexture());
	spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());
	

	cTexture rocketTxt;
	rocketTxt.createTexture("Images\\Player1.png");
	cPlayer rocketSprite;
	rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	rocketSprite.setSpritePos(glm::vec2(800.0f, 929.0f));
	rocketSprite.setTexture(rocketTxt.getTexture());
	rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
	rocketSprite.setSpriteCentre();
	rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
	rocketSprite.attachSoundMgr(theSoundMgr);// Attach sound manager to player2 sprite
	cTexture player2txt;
	player2txt.createTexture("Images\\Player2.png");
	cPlayer2 player2Sprite;
	player2Sprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
	player2Sprite.setSpritePos(glm::vec2(500.0f, 100.0f));
	player2Sprite.setTexture(player2txt.getTexture());
	player2Sprite.setTextureDimensions(player2txt.getTWidth(), player2txt.getTHeight());
	player2Sprite.setSpriteCentre();
	player2Sprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
	player2Sprite.attachSoundMgr(theSoundMgr);// Attach sound manager to rocket sprite

	
	
	int count = 0;


	PlaySound(TEXT("Audio/BackGround.wav"), NULL, SND_LOOP | SND_ASYNC);

    //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		
		pgmWNDMgr->processWNDEvents(); //Process any window events
		// Create vector array of of ai players
		if (count == 0){
		float AiStartX = 100;
		float AiStartY = 300;
		for (int astro = 0; astro < 40; astro++)
		{
			theAsteroids.push_back(new cAiPlayer);
			theAsteroids[astro]->setSpritePos(glm::vec2(AiStartX, AiStartY));
			theAsteroids[astro]->setTexture(theGameTextures[0]->getTexture());
			theAsteroids[astro]->setTextureDimensions(theGameTextures[0]->getTWidth(), theGameTextures[0]->getTHeight());
			theAsteroids[astro]->setSpriteCentre();
			theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theAsteroids[astro]->setActive(true);
			theAsteroids[astro]->setMdlRadius();
			theAsteroids[astro]->attachSoundMgr(theSoundMgr);// Attach sound manager to ai sprite
			AiStartX += 130;
			//move the down level every 10 ai
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

		}}
        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//start screen
		if (count == 0){
			rocketSprite.setLives(false);
			player2Sprite.setLives(false);
		StartspriteBkgd.render();
		PlaySprite.update(elapsedTime);
		PlaySprite.render();
		QuitSprite.update(elapsedTime);
		QuitSprite.render();
		HowSprite.update(elapsedTime);
		HowSprite.render();
		}else if (count==1){
			//play Screen
			spriteBkgd.render();
			
			rocketSprite.update(elapsedTime);
			player2Sprite.update(elapsedTime);
			vector<cAiPlayer*>::iterator asteroidIterator = theAsteroids.begin();
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

			theFontMgr->getFont("Space")->printText("Space Invaders", FTPoint(0.0f, 1.0f, 0.0f));
			theFontMgr->getFont("Space")->printScoreP2(rocketSprite.getInfo().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
			theFontMgr->getFont("Space")->printScoreP1(player2Sprite.getInfo().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
			//goes to death screen
			if (rocketSprite.getDeath() == true){
				count = 3;
			}
			if (player2Sprite.getDeath() == true){
				count = 4;
			}
		
			//shows to how to screen
		}	else if (count == 2){
			HowTospriteBkgd.render();
			HomeSprite.update(elapsedTime);
			HomeSprite.render();
			//shows death screens
		}else if (count == 3){
			
			
			spriteBkgd.render();
			player2Sprite.render();
			
			theFontMgr->getFont("Space")->endTest("Player 2 wins", FTPoint(0.0f, 1.0f, 0.0f));
			theFontMgr->getFont("Space")->printScoreP1(player2Sprite.getInfo().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
			HomeSprite.update(elapsedTime);
			HomeSprite.render();
		}else if (count == 4){
			
			spriteBkgd.render();
			rocketSprite.render();
			theFontMgr->getFont("Space")->endTest("Player 1 wins", FTPoint(0.0f, 1.0f, 0.0f));
			theFontMgr->getFont("Space")->printScoreP2(rocketSprite.getInfo().c_str(), FTPoint(0.0f, 1.0f, 0.0f));
			
			HomeSprite.update(elapsedTime);
			HomeSprite.render();
		}
		//get the butten pressed and resest all the players score
	if (HomeSprite.getPressed() == true){
		
			count = 0;
			HomeSprite.setPressed(false);
			rocketSprite.setLives(true);
			player2Sprite.setLives(true);
		}//gets button presses
		if (PlaySprite.getPressed() == true){
			
			count = 1;
			PlaySprite.setPressed(false);
			
		}
		if (QuitSprite.getPressed() == true){
			
			exit(0);
		}
		if (HowSprite.getPressed() == true){
			
			count = 2;
			HowSprite.setPressed(false);

		}
		
		

		pgmWNDMgr->swapBuffers();
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
    }

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}
