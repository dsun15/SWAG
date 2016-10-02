/**
 * S.W.A.G.
 * Chris, Devin, Kevin, William
 * 600.255 Intro to Video Game Design
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Movable.h"
using std::string;

#ifndef _AUTOMOVABLE_H
#define _AUTOMOVABLE_H

class AutoMovable: public Movable
{
	char dir;
 public:
	AutoMovable();
 AutoMovable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH,int sheetW, int sheetH): Movable(fileName,width,height,cornerX,cornerY,windowW,windowH,sheetW,sheetH) {
		srand(time(NULL));
	};
	~AutoMovable();
	void automove(int time);
	void genDir();

 private:
};

#endif
