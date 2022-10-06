// by Bacontsu, based on Color Correction tutorial from https://hlfx.ru

#include "hud.h"
#include "cl_util.h"

#include "PlatformHeaders.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl\gl.h> // Header File For The OpenGL32 Library							// Header File For The 32 Library

#include "flipview.h"

#ifndef GL_TEXTURE_RECTANGLE_NV
#define GL_TEXTURE_RECTANGLE_NV 0x84F5
#endif


CFlipScreen gFlipScene;

void CFlipScreen::InitScreen()
{
	// create a load of blank pixels to create textures with
	unsigned char* pBlankTex = new unsigned char[ScreenWidth * ScreenHeight * 3];
	memset(pBlankTex, 0, ScreenWidth * ScreenHeight * 3);

	// Create the SCREEN-HOLDING TEXTURE
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, tex);

	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, ScreenWidth, ScreenHeight, 0, GL_RGBA8, GL_UNSIGNED_BYTE, 0);

	// free the memory
	delete[] pBlankTex;
}

void CFlipScreen::DrawColorCor()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
	glEnable(GL_BLEND);

	// bind texture
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, tex);
	glCopyTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA8, 0, 0, ScreenWidth, ScreenHeight, 0);

	// enable some OpenGL stuff
	glEnable(GL_TEXTURE_RECTANGLE_NV);
	glColor3f(1, 1, 1);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, 0.1, 100);

	glBindTexture(GL_TEXTURE_RECTANGLE_NV, tex);

	glColor4f(1, 1, 1, 1);

	int width = ScreenWidth;
	int height = ScreenHeight;
	int of = 0;

	glBegin(GL_QUADS);

	glTexCoord2f(width - of, 0 - of);
	glVertex3f(0, 1, -1);
	glTexCoord2f(width - of, height + of);
	glVertex3f(0, 0, -1);
	glTexCoord2f(0 + of, height + of);
	glVertex3f(1, 0, -1);
	glTexCoord2f(0 + of, 0 - of);
	glVertex3f(1, 1, -1);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glDisable(GL_TEXTURE_RECTANGLE_NV);
	glEnable(GL_DEPTH_TEST);


	glDisable(GL_BLEND);
}
