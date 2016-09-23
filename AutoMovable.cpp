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
#include <ctime>
#include <cstdlib>
#include "Movable.h"
#include "AutoMovable.h"

using namespace std;
using std::string;

AutoMovable::AutoMovable(){};

~AutoMovable::AutoMovable(){};

void AutoMovable::automove(int time) {
	//for time based movement
	//srand(time(NULL));

	switch(this->dir) {
		case 'N':
			Movable::move(0,-1*time);
			break;
		case 'E':
			Movable::move(time,0);
			break;
		case 'S':
			Movable::move(0,time);
			break;
		case 'W':
			Movable::move(-1*time,0);
			break;
		default:
			AutoMovable::genDir();
			break;		
	}
	this->numMoves++;
	if (this.cornerX = 0) {
		this->dir = 'E';
		this->numMoves = '0';
	} else if (this.cornerY = 0) {
		this->dir = 'S';
		this->numMoves = '0';
	} else if (this->rect.x + this->rect.w = windowW) {
		this->dir = 'W';
		this->numMoves = '0';
	} else if (this->rect.y + this->rect.h > windowH) {
		this->dir = 'N';
		this->numMoves = '0';
	}
	
	//***PUT IN TERMS OF TIME***
	if (numMoves >= 5) {
		int percent = rand()%100;
		if (percent <=30) {
			AutoMovable::genDir();
			this->numMoves = '0';
		}
	}
}

void AutoMovable::genDir {
	int temp = rand()%4;
	switch(temp) {
		case 0:
			this->dir = 'N';
			break;
		case 1:
			this->dir = 'E';
			break;
		case 2:
			this->dir = 'S';
			break;
		case 3:
			this->dir = 'W';
			break;
	}
}
