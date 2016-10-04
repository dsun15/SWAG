/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Movable.h"
#include "AutoMovable.h"
#include "Screen.h"

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

class GameScreen: public Screen {
public:
	GameScreen();
	~GameScreen();
       	int input(SDL_Event * event, int dt);
	void draw(SDL_Renderer * renderer, int dt);
};

#endif
