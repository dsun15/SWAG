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
const char* effectName = "confirmClick.ogg";
const char* titleImageFile = "title.png";
SDL_Texture* titleImage;

TitleScreen::TitleScreen() {}
TitleScreen::TitleScreen(SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load(titleImageFile);
    titleImage = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
}

TitleScreen::~TitleScreen() {
    SDL_DestroyTexture(titleImage);
}

int TitleScreen::input(SDL_Event* event, int dt) {
    switch (event->type) {
    case SDL_KEYUP:
        if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_RETURN) {
            Mix_PlayChannel(-1, sfxConfirm, 0);
            return 2;
        }
        break;
    }
    dt++;
    return 0;
}

void TitleScreen::draw(SDL_Renderer* renderer, int dt) {
    SDL_RenderCopy(renderer, titleImage, NULL, NULL);
    dt++;
}
