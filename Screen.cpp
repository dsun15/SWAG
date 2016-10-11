/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include "Screen.h"
#include "AutoMovable.h"
#include "Movable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

Screen::Screen() {}

Screen::~Screen() {}

int Screen::input(SDL_Event* event, int dt) {
    if (event != NULL) {
        std::cout << std::string("input() method not overridden: ") + "dt = ";
        std::cout << dt;
        std::cout << "\n";
    }
    return 0;
}
/*
void Screen::draw(SDL_Renderer * renderer){
  if (renderer != NULL) {
    std::cout << "draw() method not overridden\n";
  }
}
*/
