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
Movable player;
AutoMovable enemy[5];
bool play[] = {true,true,true,true,true};
bool playerMoving[] = {false,false,false,false};
Mix_Chunk* sfx;
int option;
Mix_Music* music;
const char* musicName = "levelOne.ogg";
const char* effect = "bump.ogg";

GameScreen::GameScreen() {
  player =  Movable("player1.png",50,50,0,0,width,height, 600, 50);
  Mix_HaltChannel(1);
        for (int i = 0; i <=4; i++) {
	  enemy[i]  = AutoMovable("enemy1.png",50,50,(200 + 100*i),(200 + 100*i), width, height, 300, 50);
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
	//music = Mix_LoadMUS(musicName);
	//Mix_PlayMusic(music,-1);
        return;
}

GameScreen::~GameScreen() {
  //Mix_FreeMusic(music);
  if(Mix_PlayingMusic())
    Mix_PauseMusic();
}

int GameScreen::input(SDL_Event * event, int dt) {
			switch(event->type) {
			case SDL_KEYUP:
				if(event->key.keysym.sym == SDLK_RIGHT) {
					playerMoving[2]=false;				
				}
				if(event->key.keysym.sym == SDLK_LEFT) {
					playerMoving[3]=false;
				}
				if(event->key.keysym.sym == SDLK_DOWN) {
					playerMoving[0]=false;
				}
				if(event->key.keysym.sym == SDLK_UP) {
					playerMoving[1]=false;
				}
				break;
				
			case SDL_KEYDOWN:
				if(event->key.keysym.sym == SDLK_RIGHT) {
					option = 3;
					playerMoving[2] = true;
				}
				if(event->key.keysym.sym == SDLK_LEFT) {
					option = 4;
					playerMoving[3] = true;
				}
				if(event->key.keysym.sym == SDLK_DOWN) {
					option = 1;
					playerMoving[0]=true;
				}
				if(event->key.keysym.sym == SDLK_UP) {
					option = 2;
					playerMoving[1]=true;
				}
				break;
			}
			/*if (playerMoving[0] || playerMoving[1] || playerMoving[2] || playerMoving[3]) {
			  player.inputMove(dt, option);
			  }*/
	
	return 0;
}

void GameScreen::draw (SDL_Renderer * renderer, int dt) {
  player.draw(renderer,dt);
	if (playerMoving[0] || playerMoving[1] || playerMoving[2] || playerMoving[3]) {
	  player.inputMove(dt, option);
	}
	for (int i=0;i<5;i++) {
	  //*****FIX THIS AUTOMOVE SHIT*******
		enemy[i].automove(dt);
		//*******SHOULDN'T BE 2, SHOULD BE SOME TIME SHIT*********
		enemy[i].draw(renderer,dt);		
		if (player.checkCollide(&(enemy[i])) && play[i]) {
		  Mix_PlayChannel(-1, sfx,1);
			play[i] = false;
		}
		else if (!player.checkCollide(&(enemy[i]))){
			play[i] = true;

		}
	}
}
