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
int counter = 1;
TTF_Font * font;
Movable indicator;

const char * ng = "New Game";
const char * text1 = "Brightness";
const char * text2 = "Volume";
const char * text3 = "High Scores";
const char * text4 = "Quit";
const char * point = "ship.png";

SDL_Texture * tt;
SDL_Texture * t1;
SDL_Texture * t2;
SDL_Texture * t3;
SDL_Texture * t4;

SDL_Rect titlerect = {150,50,300,50};
SDL_Rect rect1 = {150,150,300,50};
SDL_Rect rect2 = {150,250,300,50};
SDL_Rect rect3 = {150,350,300,50};
SDL_Rect rect4 = {150,450,300,50};

Mix_Chunk* move;
Mix_Chunk* confirm;
const char* moveName = "moveClick.ogg";
const char* comfirmName = "confirmClick.ogg";

MenuScreen::MenuScreen(){}
MenuScreen::MenuScreen(SDL_Renderer * renderer) {
  TTF_Init();
  font = TTF_OpenFont("8bit.ttf",72);
  SDL_Color white = {255,255,255,255};
  SDL_Surface * st = TTF_RenderUTF8_Blended(font,ng,white);
  SDL_Surface * s1 = TTF_RenderUTF8_Blended(font,text1,white);
  SDL_Surface * s2 = TTF_RenderUTF8_Blended(font,text2,white);
  SDL_Surface * s3 = TTF_RenderUTF8_Blended(font,text3,white);
  SDL_Surface * s4 = TTF_RenderUTF8_Blended(font,text4,white);
  tt = SDL_CreateTextureFromSurface(renderer,st);
  t1 = SDL_CreateTextureFromSurface(renderer,s1);
  t2 = SDL_CreateTextureFromSurface(renderer,s2);
  t3 = SDL_CreateTextureFromSurface(renderer,s3);
  t4 = SDL_CreateTextureFromSurface(renderer,s4);
  indicator = Movable(point, 50,50,50,50,800,600,50,50);
	Mix_SetMusicCMD("ogg123");
	move = Mix_LoadWAV(moveName);
	confirm = Mix_LoadWAV(comfirmName);  	
}
MenuScreen::~MenuScreen(){
//	Mix_FreeMusic(move);
//	Mix_FreeMusic(confirm);
  //TTF_Quit();
}

//return ints for to determine which screen to switch to

int MenuScreen::input(SDL_Event * event, int dt){
  switch(event->type) {
  case SDL_KEYDOWN:
    if(event->key.keysym.sym == SDLK_RETURN || event->key.keysym.sym==SDLK_SPACE){
      if (counter ==1) {	
	Mix_PlayChannel(-1, confirm,0);
	return 1;
      }
      if (counter == 2){}
      if (counter == 3){}
      if (counter == 4){
	Mix_PlayChannel(-1, confirm,0);
	return 3;
      }
      if (counter == 5){
	Mix_PlayChannel(-1, confirm,0);
	return 5;
      }
    }
    if(event->key.keysym.sym ==SDLK_UP){
      if (counter>1) {
	indicator.move(0,-100);
	counter--;
      }
      Mix_PlayChannel(-1, move,0);
    }
    if(event->key.keysym.sym ==SDLK_DOWN){
      if (counter<5) {
	indicator.move(0,100);
	counter++;
      }
      Mix_PlayChannel(-1, move,0);
    }
  }
  return 0;
}

void MenuScreen::draw(SDL_Renderer * renderer, int dt){
  SDL_RenderCopy(renderer,tt,NULL,&titlerect);
  SDL_RenderCopy(renderer,t1,NULL,&rect1);
  SDL_RenderCopy(renderer,t2,NULL,&rect2);
  SDL_RenderCopy(renderer,t3,NULL,&rect3);
  SDL_RenderCopy(renderer,t4,NULL,&rect4);
  indicator.draw(renderer,dt);
}


