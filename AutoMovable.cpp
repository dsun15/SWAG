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

int timeSinceChange = 0;

AutoMovable::AutoMovable(){}

AutoMovable::~AutoMovable(){}

void AutoMovable::automove(int time) {
	//for time based movement
  if (timeSinceChange >= 2000) {
    int percent = rand()%100;                                                                  
    if (percent <=50) {                                                                        
      AutoMovable::genDir();
    }
    timeSinceChange = 0;
  }
  int speed = time / 3;
	switch(this->dir) {
		case 'N':
			Movable::move(0,-1*speed);
			break;
		case 'E':
			Movable::move(speed,0);
			break;
		case 'S':
			Movable::move(0,speed);
			break;
		case 'W':
			Movable::move(-1*speed,0);
			break;
		default:
			AutoMovable::genDir();
			break;		
	}
	if (this->rect.x == 0) {
		this->dir = 'E';
		timeSinceChange = '0';
	} else if (this->rect.y == 0) {
		this->dir = 'S';
		timeSinceChange = '0';
	} else if (this->rect.x + this->rect.w >= windowW) {
		this->dir = 'W';
		timeSinceChange = '0';
	} else if (this->rect.y + this->rect.h >= windowH) {
		this->dir = 'N';
		timeSinceChange = '0';
	}
	timeSinceChange+=time;
}

void AutoMovable::genDir() {
	int temp;
	temp = rand()%4;
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
