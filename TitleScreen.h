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

#ifndef _TITLESCREEN_H
#define _TITLESCREEN_H

class TitleScreen: public Screen {
  TTF_Font* font;
  const char * title = "SWAG DEMO";
  const char * subtitle = "Press Space to continue";
  SDL_Color textcolor = {255,255,255,255};
  SDL_Surface * textsurface;
  SDL_Surface * textsurface2;
  SDL_Texture * texture;
  SDL_Texture * texture2;
  SDL_Rect textrect;
  SDL_Rect textrect2;

public:
  TitleScreen();
  TitleScreen(SDL_Renderer *);
  ~TitleScreen();
  int input(SDL_Event * event, int dt);
  void draw(SDL_Renderer * renderer, int dt);
};

#endif
