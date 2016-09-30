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
#include "HighScoreScreen.h"
#include "Movable.h"
#include "AutoMovable.h"
#include "Screen.h"

using namespace std;

HighScoreScreen::HighScoreScreen(){}

HighScoreScreen::~HighScoreScreen(){}

//return ints for to determine which screen to switch to

int HighScoreScreen::input(SDL_Event * event, int dt){
  if (event != NULL) {
    cout << "HighScoreScreen.input() method not implemented: dt = ";
    cout << dt;
    cout << "\n";
  }
  return 0;
}

void HighScoreScreen::draw(SDL_Renderer * renderer, int dt){
  if (renderer != NULL) {
    cout << "MenuScreen.draw(() method not implemented\n";
  }
}
