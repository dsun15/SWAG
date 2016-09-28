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
	~MenuScreen();
	int input(SDL_Event *event, int dt);
	void draw(SDL_Renderer *render);

	//Font for writing menu options
	TTF_Font gFont;
	//Array of char* holding all of the menu text
	const char* menuText;
	//Color for Menu text
	SDL_Color textColor;
	//Color for selected text; change color to indicate selection(?)
	//Array(?) of surfaces and textures to write menu options
	
};

#endif

