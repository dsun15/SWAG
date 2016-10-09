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
#include "GameScreen.h"

int width = 800;
int height = 600;
SDL_Texture* gTexture;
SDL_Texture* gTexture2;
Movable door;
Movable player;
AutoMovable enemy[4];
bool gameOver = false;
bool youWin = false;
bool onScreen[] = {true, true, true, true};
bool play[] = {true,true,true,true,true};
Mix_Chunk* sfx;
int option;
Mix_Music* music;
const char* musicName = "levelOne.ogg";
const char* effect = "bump.ogg";
const char * win = "You win";
const char * lose = "You lose";
SDL_Texture * wintext;
SDL_Texture * losetext;
SDL_Rect winrect = {400,50,300,50};
SDL_Rect loserect = {400,50,300,50};

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer * renderer) {
  player =  Movable("player1.png",50,50,0,0,width,height, 600, 50);
  player.accelerate(1,0);      
  Mix_HaltChannel(1);
  Mix_Resume(1);
        for (int i = 0; i <=3; i++) {
	        enemy[i]  = AutoMovable("enemy1.png",50,50,(200 + 100i),(550), width, height, 300, 50);
        }
	if(!Mix_PausedMusic()){
	  Mix_SetMusicCMD("ogg123");
	  music = Mix_LoadMUS(musicName);
	  Mix_PlayMusic(music, -1);
	}
	else{
	  Mix_ResumeMusic();
	}
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	sfx = Mix_LoadWAV(effect);
    gameOver = false;
    youWin = false;
    for (int i = 0; i < 4; i++) {
        onScreen[i] = true;
    }
    door = Movable("player1.png",50,50,750,550, width, height, 50, 50, false);
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("8bit.ttf",72);
    SDL_Color white = {255,255,255,255};
    SDL_Surface * ws = TTF_RenderUTF8_Blended(font, win, white);
    SDL_Surface * ls = TTF_RenderUTF8_Blended(font, lose, white);
    wintext = SDL_CreateTextureFromSurface(renderer,ws);
    losetext = SDL_CreateTextureFromSurface(renderer,ls);
    return;
    
}

GameScreen::~GameScreen() {
  //Mix_FreeMusic(music);
  if(Mix_PlayingMusic())
    Mix_PauseMusic();
}

int GameScreen::input(SDL_Event * event, int dt) {
			if (gameOver) {
                return 3;
            }
            if (youWin) {
        
                return 3;
            }
            switch(event->type) {
			case SDL_KEYUP:
				if(event->key.keysym.sym == SDLK_RIGHT) {
				  player.setMove(false);
				}
				if(event->key.keysym.sym == SDLK_LEFT) {
				  player.setMove(false);
				}
				if(event->key.keysym.sym == SDLK_DOWN) {
				}
				if(event->key.keysym.sym == SDLK_UP) {
				}
				break;
				
			case SDL_KEYDOWN:
				if(event->key.keysym.sym == SDLK_RIGHT) {
					option = 3;
					player.accelerate(dt, 2);
					player.setMove(true);
				}
				if(event->key.keysym.sym == SDLK_LEFT) {
					option = 4;
					player.accelerate(dt, -2);
					player.setMove(true);
				}
				if(event->key.keysym.sym == SDLK_DOWN) {
					option = 1;
				}
				if(event->key.keysym.sym == SDLK_SPACE) {
					option = 2;
					player.jump();
				}
				break;
			}
	return 0;
}

void GameScreen::draw (SDL_Renderer * renderer, int dt) {
  player.draw(renderer,dt);
  door.draw(renderer,dt);
        
        if (player.checkCollide(&door)) {
            youWin = true;
        } 
		for (int i=0;i<4;i++) {
            //check collisions
            if (player.checkCollide(&(enemy[i])) && onScreen[i]) {
                //jump on enemy for a kill
                SDL_Rect * temp = player.getRect();
                SDL_Rect * enemyTemp = enemy[i].getRect();
                if((temp->y < enemyTemp->y) && (abs(temp->x - enemyTemp->x) <= enemyTemp->w)) {
                    onScreen[i] = false;  
                //you die 
                } else {
                    gameOver = true;
                }

            }  

            //render enemeies 
            if(onScreen[i]){
		        enemy[i].automove(dt);
		        enemy[i].draw(renderer,dt);		
            }

        }
}
