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
#include "TitleScreen.h"
#include "HighScoreScreen.h"

const int width = 800;
const int height = 600;
const char* title = "Game Engine Demo";
const char* bigtext = "replace this text later";
//const char* gameMusic = "levelOne.ogg";
//const char* titleMusicTitle = "title.ogg";
const double radToDeg = 180 / M_PI;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
//Mix_Music* titleMusic;
//Mix_Music* game;
GameScreen  g;
TitleScreen t;
MenuScreen m;
HighScoreScreen h;
Screen * activeScreen;

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
	
	Mix_SetMusicCMD("ogg123");
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

	t = TitleScreen(gRenderer);
   	m = MenuScreen(gRenderer);
       	h = HighScoreScreen(gRenderer);
    g = GameScreen(gRenderer);
	return;
}

void load() {
//	titleMusic = Mix_LoadMUS(titleMusicTitle);
//	game = Mix_LoadMUS(gameMusic);
	std::cout << "loaded music" << "\n";
	activeScreen = &t;
	return;
}

void cleanup() {
	//Mix_FreeMusic(gMusic);
	//Mix_FreeMusic(sfx);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
       	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void run() {
	SDL_Event event;
	bool running = true;
	unsigned int lastTime = 0;
	unsigned int currentTime;
	double time = 0.0;
	int screenswitch = 0;
	while(running) {
		currentTime = SDL_GetTicks();
		unsigned int dt = currentTime - lastTime;
		time += (double) dt / 1000.00;
		lastTime = currentTime;
		
		while(SDL_PollEvent(&event) != 0) {
		        screenswitch = activeScreen->input(&event, dt);
			switch(event.type) {
			
			case SDL_QUIT:
			  Mix_HaltMusic();
				running = false;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
				  Mix_HaltMusic();
				  running = false;
				}
				if(event.key.keysym.sym == SDLK_p) {
				  screenswitch = 2; 
				}
				break;
			}
		}
			if (screenswitch == 1) {
			  //new game
			  g = GameScreen(gRenderer);
			  activeScreen = &g;
			  std::cout << "triggered screen switch\n";
			}
			if (screenswitch == 2) {
			  //menu
			  activeScreen = &m;
			}
			if (screenswitch == 3) {
			  //high score
			  activeScreen = &h;
			}
			if (screenswitch == 4) {
			  //title
			  activeScreen = &t;
			}
			if (screenswitch == 5) {
			  Mix_HaltMusic();
			  running = false;
			}
			SDL_RenderClear(gRenderer);
			activeScreen->draw(gRenderer, dt);
			SDL_RenderPresent(gRenderer);
			screenswitch = 0;
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
