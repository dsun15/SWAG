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

#ifndef _SCREEN_H
#define _SCREEN_H

class Screen {

public:
	Screen();
	~Screen();
	virtual int input(SDL_Event * event, int dt) =0; /*{
	  if (event != NULL) {
	    std::cout << std::string("input() method not overridden: ") + "dt = ";
	    std::cout << dt;
	    std::cout << "\n";
	  }
	  return 0;
	  }*/

	virtual void draw(SDL_Renderer * renderer, int dt){
	  if (renderer != NULL) {
	    std::cout << "draw() method not overridden: dt = ";
	    std::cout << dt;
	    std::cout <<"\n";
	  }
	};
};

#endif

