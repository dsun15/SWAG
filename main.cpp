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

const int width = 800;
const int height = 600;
const char* title = "Game Engine Demo";
const char* bigtext = "replace this text later";
const char* musicTitle = "sqPP.wav";
//const double twoPi = 2 * M_PI;
const double radToDeg = 180 / M_PI;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;
SDL_Texture* gTexture2;
Movable player;
Movable enemy;

Mix_Music* gMusic;
//TTF_Font* gFont;
//TTF_Font* gFont2;

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
	std::cout << "loaded music" << "\n";
	
	player =  Movable("ship.png",50,50,0,0,width,height);

	SDL_Surface* hero = IMG_Load("ship.png");
	SDL_Surface* enemy = IMG_Load("baddie.png");
	if(!hero) {
    	std::cout << "IMG_Load: " << IMG_GetError() << "\n";
	}
	
	gTexture = SDL_CreateTextureFromSurface(gRenderer, hero);
	gTexture2 = SDL_CreateTextureFromSurface(gRenderer, enemy);
	if (gTexture || gTexture2 == NULL) {
		std::cout << "Something broke in load: " << SDL_GetError();
	}
	
	return;
}

void cleanup() {
	Mix_FreeMusic(gMusic);
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
	int textureW;
	int textureH;
	textureSize(gTexture, &textureW, &textureH);
	SDL_Rect  textureRect = {center(width, textureW), center(height, textureH),
							 textureW, textureH};
	SDL_Rect  textureRect2 = {center(width, textureW)+100, center(height, textureH),
							 textureW, textureH};
	//SDL_Rect  textureRect2 = {width/2-textureW/16, height/2-textureW/16, textureW/8, textureW/8};
//	SDL_Rect  shadowRect = {center(width, shadow->w), center(height, shadow->h),
//							shadow->w, shadow->h};
//	SDL_Rect  textRect = {center(width, text->w), center(height, text->h),
//						  text->w, text->h};
	
	while(running) {
		currentTime = SDL_GetTicks();
		unsigned int dt = currentTime - lastTime;
		time += (double) dt / 1000.00;
		lastTime = currentTime;
		
		/**if( time > twoPi) {
			time -= twoPi;
		}*/
		
		while(SDL_PollEvent( &event ) != 0) {
			switch(event.type) {
			
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
				break;
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_RIGHT) {
					player.move(5,0);
				}
				if(event.key.keysym.sym == SDLK_LEFT) {
					player.move(-5,0);
				}
				if(event.key.keysym.sym == SDLK_DOWN) {
					player.move(0,5);
				}
				if(event.key.keysym.sym == SDLK_UP) {
					player.move(0,-5);
				}
				break;
			}
		
		}
	
		SDL_RenderClear(gRenderer);

		
		if (SDL_RenderCopyEx(gRenderer, gTexture, NULL, &textureRect,
						 radToDegs(time), NULL, SDL_FLIP_NONE) < 0) {
			std::cout << "Something broke1: " << SDL_GetError();
		}
		if (SDL_RenderCopyEx(gRenderer, gTexture2, NULL, &textureRect2,
						 radToDegs(sin(time)), NULL,SDL_FLIP_NONE) < 0) {
			std::cout << "Something broke2: " << SDL_GetError();
		}

		player.draw(gRenderer);
						 
	//	if (SDL_RenderCopy(gRenderer, shadowex, NULL, &shadowRect) < 0) {
	//		std::cout << "Something broke: " << SDL_GetError();
	//	}
		
	//	if (SDL_RenderCopy(gRenderer, textex, NULL, &textRect) < 0) {
	//		std::cout << "Something broke: " << SDL_GetError();
	//	}
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
                                        



	
