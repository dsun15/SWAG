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
#include "TitleScreen.h"
#include "Screen.h"

Mix_Chunk* titleMusic;
Mix_Chunk* sfxConfirm;
const char* musicTitleName = "title.ogg";
const char* effectName = "confirmClick.ogg";

TitleScreen::TitleScreen() {}
TitleScreen::TitleScreen(SDL_Renderer * renderer){
  TTF_Init();
  this->font = TTF_OpenFont("8bit.ttf", 72);
  this->textsurface = TTF_RenderUTF8_Blended(this->font,this->title,this->textcolor);
  this->textsurface2 = TTF_RenderUTF8_Blended(this->font,this->subtitle,this->textcolor);
  this->texture = SDL_CreateTextureFromSurface(renderer,textsurface);
  this->texture2 = SDL_CreateTextureFromSurface(renderer, textsurface2);
  this->textrect = {50,50,400,50};
  this->textrect2 = {50,300,300,50};
  Mix_SetMusicCMD("ogg123");
  titleMusic = Mix_LoadWAV(musicTitleName);
  Mix_PlayChannel(1, titleMusic, -1);
  sfxConfirm = Mix_LoadWAV(effectName);
}

TitleScreen::~TitleScreen(){
  //TTF_CloseFont(this->font);
  //  TTF_Quit();

}

int TitleScreen::input(SDL_Event * event, int dt){
  switch (event->type) {
  case SDL_KEYUP:
    if(event->key.keysym.sym == SDLK_SPACE) {
	Mix_PlayChannel(-1,sfxConfirm,1);
	return 1;
    }
    break;
  }
  return 0;
}

void TitleScreen::draw(SDL_Renderer * renderer, int dt){
  SDL_RenderCopy(renderer,texture,NULL,&(this->textrect));
  SDL_RenderCopy(renderer,texture2,NULL,&(this->textrect2));
}


