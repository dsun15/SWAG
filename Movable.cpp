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

//using namespace Movable;
using namespace std;
using std::string;

Movable::Movable(){}

Movable::Movable(string fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH){ 
	this->fileName = fileName;
	if (width < 0 || height < 0 || cornerX < 0 || cornerY < 0 || windowW < 0 || windowH < 0) {
		cout << "something's negative/n";
	}	
	if (cornerX+width > windowW || cornerY+height > windowH) {
		cout << "beyond window boundaries/n";
	}
	this->width = width;
	this->height = height;
	this->cornerX = cornerX;
	this->cornerY = cornerY;
	this->windowW = windowW;
	this->windowH = windowH;
	//MAKE THE SDL RECT HERE
}	

Movable::Movable(const Movable & m) {
	this->fileName = m.fileName;
	this->width = m.width;
	this->height = m.height;
	this->cornerX = m.cornerX;
	this->cornerY = m.cornerY;
	this->windowW = m.windowW;
	this->windowH = m.windowH;
	this->rect = m.rect;
}

Movable::~Movable() {}

void Movable::move(int x, int y) {
	this->cornerX += x;
	this->cornerY += y;
	if (cornerX < 0) {
		cornerX = 0;
	}
	if (cornerY < 0) {
		cornerY = 0;
	}
	if (cornerX + width > windowW) {
		cornerX = windowW - width;
	}
	if (cornerY + height > windowH) {
		cornerY = windowH - height;
	}
}

bool Movable::checkCollide(Movable * m) {
	const SDL_Rect * r1 = &(this->rect);
	const SDL_Rect * r2 = &(m->rect);
	return SDL_HasIntersection(r1, r2);
}
