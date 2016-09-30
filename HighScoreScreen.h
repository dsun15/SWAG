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
#include <vector>
#include "Screen.h"
#include "Movable.h"
#include "AutoMovable.h"

#ifndef _HIGHSCORE_SCREEN_H
#define _HIGHSCORE_SCREEN_H

using namespace std;

class HighScoreScreen: public Screen {

  
public:
	HighScoreScreen();
	HighScoreScreen(SDL_Renderer *);
	~HighScoreScreen();
	
	int input(SDL_Event * event, int dt);
	void draw(SDL_Renderer * renderer, int dt);
};

#endif

