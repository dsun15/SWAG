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
#include <stdlib.h>
#include "Movable.h"

//using namespace Movable;
using namespace std;
using std::string;

Movable::Movable(){}

Movable::Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH, int sheetWidth, int sheetHeight){ 
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
	this->spriteSheetRect = {0,0,50,50};
	this->sheetWidth = sheetWidth;
	this->sheetHeight = sheetHeight;
}

Movable::Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH, int sheetWidth, int sheetHeight, bool hasGravity){ 
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
	this->spriteSheetRect = {0,0,50,50};
	this->sheetWidth = sheetWidth;
	this->sheetHeight = sheetHeight;
	if(!hasGravity)
	  this->gravity = 0;
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

void Movable::accelerate(int dt, int accX) {
	this->velX = this->velX + accX*dt;
	this->velY = this->velY + this->gravity*(dt/3);
	if (abs(this->velX) > MAX_HORIZ) {
		if (this->velX >0) {
			this->velX = MAX_HORIZ;
		} else if (this->velX<0) {
			this->velX = -1*MAX_HORIZ;
		}
	}
	if (velY > MAX_VERT) {
		if (this->velY > 0) {
			this->velY = MAX_VERT;
		} else if (this->velY < 0) {
			this->velY = -1*MAX_VERT;
		}
	}
}


		

void Movable::move(int dt) {
	//setting
	this->rect.x += this->velX * dt;
	this->rect.y += this->velY * dt;
	if (!this->isMoving) {
	  if(this->velX>0) {
	    Movable::accelerate(dt,-1);
	  }
	  if (this->velX < 0) {
	    Movable::accelerate(dt,1);
	  }
	}
	Movable::accelerate(dt,0);
       
	//checking for boundary collisions
	if (this->rect.x < 0) {
		this->rect.x = 0;
		this->velX = 0;
	}
	if (this->rect.y < 0) {
		this->rect.y = 0;
		this->velY = 0;
	}
	if (this->rect.x + this->rect.w > windowW) {
		this->rect.x = windowW - this->rect.w;
		this->velX = 0;
	}
	if (this->rect.y + this->rect.h > windowH) {
		this->rect.y = windowH - this->rect.h;
		this->velY = 0;
		this->inAir = false;
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
		this->inAir = false;
	}
}

bool Movable::checkCollide(Movable * m) {
	const SDL_Rect * r1 = &(this->rect);
	const SDL_Rect * r2 = &(m->rect);
	return SDL_HasIntersection(r1, r2);
}

bool Movable::checkCollide(SDL_Rect * rect) {
  const SDL_Rect * temp = &(this->rect);
  return SDL_HasIntersection(temp, rect);
}

void Movable::draw(SDL_Renderer * renderer, int dt) {
  Movable::move(dt);
  spriteUpdate(dt);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->img);
  SDL_RenderCopy(renderer, texture, &(this->spriteSheetRect), &(this->rect));
}

void Movable::spriteUpdate(int dt) {
  if (this->timeSinceSpriteChange >= 80) {
    this->spriteSheetRect.x+=50;
    if (this->spriteSheetRect.x >=sheetWidth) {
      this->spriteSheetRect.x = 0;
    }
    this->timeSinceSpriteChange = 0;
  }
  this->timeSinceSpriteChange+=dt;
}

void Movable::setMove(bool b) {
  this->isMoving = b;
}

void Movable::setVelX(int n) {
  this->velX = n;
}

void Movable::setVelY(int n) {
  this->velY = n;
}

void Movable::jump() {
  if (!this->inAir) {
    this->inAir = true;
    Movable::setVelY(-4);;
  }
}

SDL_Rect * getRect() {
  return &(this->rect);
}
