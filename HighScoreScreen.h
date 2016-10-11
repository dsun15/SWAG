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
#include <fstream>
#include <iostream>
#include <iostream>
#include <string>
#include <vector>

#ifndef _HIGHSCORE_SCREEN_H
#define _HIGHSCORE_SCREEN_H

using namespace std;

class HighScoreScreen : public Screen {

protected:
    string names[5] = { "1st", "2nd", "3rd", "4th", "5th" };
    int scores[5];
    string filename;

public:
    HighScoreScreen();
    HighScoreScreen(SDL_Renderer*);
    ~HighScoreScreen();

    int input(SDL_Event* event, int dt);
    void draw(SDL_Renderer* renderer, int dt);
};

#endif
