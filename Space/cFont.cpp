/*
==========================================================================
cFont.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cFont.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/
cFont::cFont()
{
	theFont = NULL;
}
/*
==========================================================================
Overloaded constructor
==========================================================================
*/
cFont::cFont(LPCSTR fontFileName, int fontSize)
{
	theFont = new FTTextureFont(fontFileName);

	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}

/*
==========================================================================
Destructor
==========================================================================
*/
cFont::~cFont()
{
	delete theFont;
}
/*
==========================================================================
get the pointer to the font
==========================================================================
*/
FTFont* cFont::getFont()
{
	return theFont;
}

/*
==========================================================================
Render the text using the desired font
==========================================================================
*/
void cFont::printText(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glColor3f(0.0f, 255.0f, 0.0f);
	glTranslatef(13, 17, 0);
	glRotatef(180, 0, 0, -1);
	glRotatef(180, 0, -1, 0);

	theFont->Render(text,  -1, textPos);

	glPopMatrix();
}
//display players data
void cFont::printScoreP1(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glColor3f(0.0f, 255.0f, 0.0f);
	glTranslatef(1300, 17, 0);
	glRotatef(180, 0, 0, -1);
	glRotatef(180, 0, -1, 0);

	theFont->Render(text, -1, textPos);

	glPopMatrix();
}//display players data
void cFont::printScoreP2(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glColor3f(0.0f, 255.0f, 0.0f);
	glTranslatef(1300, 800, 0);
	glRotatef(180, 0, 0, -1);
	glRotatef(180, 0, -1, 0);

	theFont->Render(text, -1, textPos);

	glPopMatrix();
}
void cFont::endTest(LPCSTR text, FTPoint textPos)
{
	glPushMatrix();

	glColor3f(0.0f, 255.0f, 0.0f);
	glTranslatef(900, 500, 0);
	glRotatef(180, 0, 0, -1);
	glRotatef(180, 0, -1, 0);

	theFont->Render(text, -1, textPos);

	glPopMatrix();
}

