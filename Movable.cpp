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

Movable::Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH){ 
	this->fileName = fileName;
	if (width < 0 || height < 0 || cornerX < 0 || cornerY < 0 || windowW < 0 || windowH < 0) {
		cout << "something's negative\n";
	}	
	if (cornerX+width > windowW || cornerY+height > windowH) {
		cout << "beyond window boundaries\n";
	}
	this->windowW = windowW;
	this->windowH = windowH;
	this->rect = {cornerX, cornerY, width, height};
	this->img = IMG_Load(fileName);
	
}	

Movable::Movable(const Movable & m) {
	this->fileName = m.fileName;
	this->windowW = m.windowW;
	this->windowH = m.windowH;
	this->rect = m.rect;
	this->img = IMG_Load(fileName);
}

Movable::~Movable() {
	
}

void Movable::inputMove(int dt, int direction) {
	switch (direction) {
		//down
		case 1:
			move(0,dt);	
			break;
		//up
		case 2:
			move(0,-1*dt);
			break;
		//right
		case 3:
			move(dt, 0);
			break;
		//left
		case 4:
			move(-1*dt, 0);
			break;
	}
}
		

void Movable::move(int x, int y) {
	//setting
	this->rect.x += x;
	this->rect.y += y;
	//checking for boundary collisions
	if (this->rect.x < 0) {
		this->rect.x = 0;
	}
	if (this->rect.y < 0) {
		this->rect.y = 0;
	}
	if (this->rect.x + this->rect.w > windowW) {
		this->rect.x = windowW - this->rect.w;
	}
	if (this->rect.y + this->rect.h > windowH) {
		this->rect.y = windowH - this->rect.h;
	}
}

bool Movable::checkCollide(Movable * m) {
	const SDL_Rect * r1 = &(this->rect);
	const SDL_Rect * r2 = &(m->rect);
	return SDL_HasIntersection(r1, r2);
}

void Movable::draw(SDL_Renderer * renderer) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->img);
	SDL_RenderCopy(renderer, texture, NULL, &(this->rect));
}
