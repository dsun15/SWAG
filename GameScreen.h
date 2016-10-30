/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include "AutoMovable.h"
#include "Movable.h"
#include "Screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

class GameScreen : public Screen {
public:
    GameScreen();
    GameScreen(SDL_Renderer* renderer);
    ~GameScreen();
    int input(SDL_Event* event, int dt);
    void draw(SDL_Renderer* renderer, int dt);
    void reset();
    void hardReset();
    void advanceLevel();
};

#endif
