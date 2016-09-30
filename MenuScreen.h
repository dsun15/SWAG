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
#include "Screen.h"
#include "Movable.h"
#include "AutoMovable.h"

#ifndef _MENU_SCREEN_H
#define _MENU_SCREEN_H

class MenuScreen: public Screen {

public:
	MenuScreen();
	MenuScreen(SDL_Renderer *);
	~MenuScreen();

	int input(SDL_Event * event, int dt);
	void draw(SDL_Renderer * renderer, int dt);
};

#endif

