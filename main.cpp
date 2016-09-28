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
#include "MenuScreen.h"

const int width = 800;
const int height = 600;
const char* title = "Game Engine Demo";
const char* bigtext = "replace this text later";
const char* musicTitle = "sqPP.wav";
//const char* effect = "bump.wav";
//const double twoPi = 2 * M_PI;
const double radToDeg = 180 / M_PI;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
//SDL_Texture* gTexture;
//SDL_Texture* gTexture2;
//Movable player;
//AutoMovable enemy[5];
Mix_Music* gMusic;
//Mix_Music* sfx;
//TTF_Font* gFont;
//TTF_Font* gFont2;
GameScreen g = GameScreen();
Screen activeScreen = g;

int center(int large, int small) {

	return large/2 - small/2;
}

double radToDegs(double r) {
	return r * radToDeg;
}

void textureSize(SDL_Texture * t, int* w, int* h) {
	SDL_QueryTexture(t, NULL, NULL, w, h);
	return;
}

// Set up all the basic SDL bits and pieces we'll need.
void setup() {
	
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "oops. Failed to init: " << SDL_GetError() << "\n";
	}
	
	if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 ) { 
   	std::cerr <<"SDL_mixer could not initialize! SDL_mixer Error:"
    			  << Mix_GetError() << "\n";
    	}
    
//   	TTF_Init();
   	gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, 
   							  SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
   	if(gWindow == NULL) {
	   std::cout << "Something broke in setup1: " << SDL_GetError();
	}
	
   	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
   	if(gRenderer == NULL) {
	   std::cout << "Something broke insetup2: " << SDL_GetError();
	}
	
   	return;
}

void load() {
	gMusic = Mix_LoadMUS(musicTitle);
	//sfx = Mix_LoadMUS(effect);
	std::cout << "loaded music" << "\n";
	
	//player =  Movable("PlayerSprite.xcf",50,50,0,0,width,height);
	//for (int i = 0; i <=4; i++) {
	//	enemy[i]  = AutoMovable("EnemySprite.xcf",50,50,(200 + 100*i),(200 + 100*i), width, height);
	//}
	activeScreen = g;
	return;
}

void cleanup() {
	Mix_FreeMusic(gMusic);
	//Mix_FreeMusic(sfx);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
//	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void run() {
	SDL_Event event;
	bool running = true;
	unsigned int lastTime = 0;
	unsigned int currentTime;
	double time = 0.0;
	//SDL_Color blue = {0,0,255,255};
	//SDL_Surface* text = TTF_RenderUTF8_Blended(gFont, bigtext, blue);
	//SDL_Texture* textex =  SDL_CreateTextureFromSurface(gRenderer, text);
	//SDL_Color black ={0,0,0,255};
	//SDL_Surface* shadow = TTF_RenderUTF8_Blended(gFont2, bigtext, black);
	//SDL_SetSurfaceAlphaMod(shadow, 128);
	//SDL_Texture* shadowex =  SDL_CreateTextureFromSurface(gRenderer, shadow);
	/**bool play[] = {true,true,true,true,true};
	int option;
	double timePress;
	bool playerMoving[] = {false,false,false,false};*/	
	while(running) {
		currentTime = SDL_GetTicks();
		unsigned int dt = currentTime - lastTime;
		time += (double) dt / 1000.00;
		lastTime = currentTime;
		
		if( time > 4) {
			time -= 2;
		}
		

		while(SDL_PollEvent( &event ) != 0) {
		  activeScreen.input(&event, dt);
			switch(event.type) {
			
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				
				/*if(event.key.keysym.sym == SDLK_RIGHT) {
					//timePress = (currentTime - timePress) / 1000.0;
					playerMoving[2]=false;				
				}
				if(event.key.keysym.sym == SDLK_LEFT) {
					//timePress = (currentTime - timePress) / 1000.0;
					playerMoving[3]=false;
				}
				if(event.key.keysym.sym == SDLK_DOWN) {
					//timePress = (currentTime - timePress) / 1000.0;
					playerMoving[0]=false;
				}
				if(event.key.keysym.sym == SDLK_UP) {
					//timePress = (currentTime - timePress) / 1000.0;
					playerMoving[1]=false;
					}*/
				break;
				
				/*case SDL_KEYDOWN:
				timePress = SDL_GetTicks(); 
				if(event.key.keysym.sym == SDLK_RIGHT) {
					option = 3;
					playerMoving[2] = true;
					//player.inputMove(timePress, 3);
				}
				if(event.key.keysym.sym == SDLK_LEFT) {
					option = 4;
					playerMoving[3] = true;
					//player.inputMove(timePress,4);
				}
				if(event.key.keysym.sym == SDLK_DOWN) {
					option = 1;
					playerMoving[0]=true;
					//player.inputMove(timePress, 1);
				}
				if(event.key.keysym.sym == SDLK_UP) {
					option = 2;
					playerMoving[1]=true;
					//player.inputMove(timePress, 2);
					}*/
				break;
			}
		
		}
		/*if (playerMoving[0] || playerMoving[1] || playerMoving[2] || playerMoving[3]) {
			player.inputMove(dt, option);
			}*/
		SDL_RenderClear(gRenderer);
		activeScreen.draw(gRenderer);
		//player.draw(gRenderer);
		/*for (int i=0;i<5;i++) {
			enemy[i].automove(time);
			enemy[i].draw(gRenderer);		
			if (player.checkCollide(&(enemy[i])) && play[i]) {
				Mix_PlayMusic(sfx,0);
				play[i] = false;
			}
			else if (!player.checkCollide(&(enemy[i]))){
				play[i] = true;
			}
			}*/
		SDL_RenderPresent(gRenderer);
		
	}
	
	return;
}

int main() {
	setup();
	
	load();
	
//	Mix_PlayMusic(gMusic, -1);
	
	run();
	
	cleanup();
	
	return 0;
}
