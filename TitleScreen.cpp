/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include "TitleScreen.h"
#include "AutoMovable.h"
#include "MenuScreen.h"
#include "Movable.h"
#include "Screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

Mix_Chunk* titleMusic;
Mix_Chunk* sfxConfirm;
//const char* musicTitleName = "title.ogg";
const char* effectName = "confirmClick.ogg";
const char* titleImageFile = "title.png";
SDL_Texture* titleImage;

TitleScreen::TitleScreen() {}
TitleScreen::TitleScreen(SDL_Renderer* renderer) {
  //TTF_Init();
    /*this->font = TTF_OpenFont("8bit.ttf", 72);
    this->textsurface = TTF_RenderUTF8_Blended(this->font, this->title, this->textcolor);
    this->textsurface2 = TTF_RenderUTF8_Blended(this->font, this->subtitle, this->textcolor);
    this->texture = SDL_CreateTextureFromSurface(renderer, textsurface);
    this->texture2 = SDL_CreateTextureFromSurface(renderer, textsurface2);
    this->textrect = { 50, 50, 400, 50 };
    this->textrect2 = { 50, 300, 300, 50 };*/
  std::cout << "?" << std::endl;
  //SDL_Surface * surf = IMG_Load("title.xcf");
  SDL_Surface * surf = IMG_Load(titleImageFile);
  std::cout << "?" << std::endl;
    titleImage = SDL_CreateTextureFromSurface(renderer, surf);
    std::cout << "?" << std::endl;    
SDL_FreeSurface(surf);
 std::cout << "?" << std::endl;
/*    Mix_SetMusicCMD("ogg123");
    titleMusic = Mix_LoadWAV(musicTitleName);
    Mix_PlayChannel(1, titleMusic, -1);
    sfxConfirm = Mix_LoadWAV(effectName);*/
}

TitleScreen::~TitleScreen() {
    //TTF_CloseFont(this->font);
    //  TTF_Quit();
  SDL_DestroyTexture(titleImage);
}

int TitleScreen::input(SDL_Event* event, int dt) {
    switch (event->type) {
    case SDL_KEYUP:
        if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_RETURN) {
            Mix_PlayChannel(-1, sfxConfirm, 0);
            return 1;
        }
        break;
    }
    dt++;
    return 0;
}

void TitleScreen::draw(SDL_Renderer* renderer, int dt) {
  //std::cout << "giggle" << std::endl;
  SDL_RenderCopy(renderer,titleImage, NULL, NULL);
  //SDL_RenderCopy(renderer, texture, NULL, &(this->textrect));
  //SDL_RenderCopy(renderer, texture2, NULL, &(this->textrect2));
    dt++;
}
