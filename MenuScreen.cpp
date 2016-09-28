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
#include "MenuScreen.h"
#include "Movable.h"
#include "AutoMovable.h"
#include "Screen.h"

MenuScreen::MenuScreen(){}

MenuScreen::~MenuScreen(){}

//return ints for to determine which screen to switch to

int MenuScreen::input(SDL_Event * event, int dt){
  if (event != NULL) {
    std::cout << std::string("MenuScreen.input() method not implemented: ") + "dt = ";
    std::cout << dt;
    std::cout << "\n";
  }
  return 0;
}

void MenuScreen::draw(SDL_Renderer * renderer, int dt){
  if (renderer != NULL) {
    std::cout << std::string("MenuScreen.draw(() method not implemented\n");
  }
}


