/* 
* S.W.A.G.
* Chris, Devin, Kevin, William
* 600.255 Intro to Video Game Design
*
*/

#include "Movable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <stdlib.h>
#include <string>

//using namespace Movable;
using namespace std;
using std::string;

Movable::Movable() {}

Movable::Movable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetWidth, int sheetHeight) {
    this->fileName = fileName;
    if (width < 0 || height < 0 || cornerX < 0 || cornerY < 0 || levelWidth < 0 || levelHeight < 0) {
        cout << "something's negative\n";
    }
    if (cornerX + width > levelWidth || cornerY + height > levelHeight) {
        cout << "beyond window boundaries\n";
    }
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->rect = { cornerX, cornerY, width, height };
    this->img = IMG_Load(fileName);
    //this->spriteSheetRect = { 0, 0, 50, 50 };
    this->spriteSheetRect = {0,0,width,height};
    this->sheetWidth = sheetWidth;
    this->sheetHeight = sheetHeight;
    this->truex = cornerX;
    this->truey = cornerY;
    this->animate = true;
    this->leftBound = 0;
    this->rightBound = levelWidth;
    this->upperBound = 0;
    this->lowerBound = levelHeight;
    this->inAir = true;
}

Movable::Movable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetWidth, int sheetHeight, bool hasGravity, bool anim) {
    this->fileName = fileName;
    if (width < 0 || height < 0 || cornerX < 0 || cornerY < 0 || levelWidth < 0 || levelHeight < 0) {
        cout << "something's negative\n";
    }
    if (cornerX + width > levelWidth || cornerY + height > levelHeight) {
        cout << "beyond window boundaries\n";
    }
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->rect = { cornerX, cornerY, width, height };
    this->truerect = {cornerX, cornerY, width, height};
    this->img = IMG_Load(fileName);
    this->spriteSheetRect = {0,0,width,height};
    // this->spriteSheetRect = { 0, 0, 50, 50 };
    this->sheetWidth = sheetWidth;
    this->sheetHeight = sheetHeight;
    if (!hasGravity)
        this->gravity = 0;
    this->hasGrav = hasGravity;
    this->truex = cornerX;
    this->truey = cornerY;
    this->animate = anim;
    this->leftBound = 0;
    this->rightBound = levelWidth;
    this->upperBound = 0;
    this->lowerBound = levelHeight;
    this->inAir = true;
}

Movable::~Movable() {
}

void Movable::accelerate(int dt, int accX) {
    this->velX = this->velX + accX * dt;
    //    if (this->inAir) {
      this->velY = this->velY + this->gravity * (dt / 2);
      //}
    if (abs(this->velX) > MAX_HORIZ) {
        if (this->velX > 0) {
            this->velX = MAX_HORIZ;
        } else if (this->velX < 0) {
            this->velX = -1 * MAX_HORIZ;
        }
    }
    if (velY > MAX_VERT) {
        if (this->velY > 0) {
            this->velY = MAX_VERT;
        } else if (this->velY < 0) {
            this->velY = -1 * MAX_VERT;
        }
    }
}

void Movable::move(int dt) {
    this->rect.x = this->truex;
    this->rect.y = this->truey;
  
    //setting
    dt = dt / 2;
    this->rect.x += this->velX * dt;
    this->rect.y += this->velY * dt;
    if (!this->isMoving) {
      /*if (this->velX > 0) {
            Movable::accelerate(dt, -1);
        }
        if (this->velX < 0) {
            Movable::accelerate(dt, 1);
	    }*/
      this->velX = 0;
    }
    Movable::accelerate(dt, 0);

    //checking for boundary collisions
    if (this->rect.x < this->leftBound) {
        this->rect.x = this->leftBound;
//        this->velX = 0;
    }
    if (this->rect.y < this->upperBound) {
        this->rect.y = this->upperBound;
        this->velY = 0;
    }
    if (this->rect.x + this->rect.w > this->rightBound) {
        this->rect.x = this->rightBound - this->rect.w;
//        this->velX = 0;
    }
    if (this->rect.y + this->rect.h > this->lowerBound) {
        this->rect.y = this->lowerBound - this->rect.h;
        this->velY = 0;
        this->inAir = false;
    }

    this->truex = this->rect.x;
    this->truey = this->rect.y;
}

void Movable::move(int x, int y) {
    this->rect.x = this->truex;
    this->rect.y = this->truey;
  
    //setting
    this->rect.x += x;
    this->rect.y += y;
    //checking for boundary collisions
    if (this->rect.x < this->leftBound) {
        this->rect.x = this->leftBound;
    }
    if (this->rect.y < this->upperBound) {
        this->rect.y = this->upperBound;
    }
    if (this->rect.x + this->rect.w > this->rightBound) {
        this->rect.x = this->rightBound - this->rect.w;
    }
    if (this->rect.y + this->rect.h > this->lowerBound) {
        this->rect.y = this->lowerBound - this->rect.h;
        this->inAir = false;
    }

    this->truex = this->rect.x;
    this->truey = this->rect.y;
}

void Movable::translate(int x, int y) {
    //setting
    this->rect.x += x;
    this->rect.y += y;
}

bool Movable::checkCollide(Movable* m) {
  const SDL_Rect temp = {this->truex, this->truey, this->rect.w, this->rect.h}; 
  //const SDL_Rect* r1 = &(this->rect);
  const SDL_Rect* r2 = m->getTrueRect();;
    return SDL_HasIntersection(&temp, r2);
}

bool Movable::checkCollide(SDL_Rect* rect) {
  //const SDL_Rect* temp = &(this->rect);
  const SDL_Rect temp = {this->truex, this->truey, this->rect.w, this->rect.h};  
  return SDL_HasIntersection(&temp, rect);
}

void Movable::draw(SDL_Renderer* renderer, int dt, int transx, int transy, bool onGround) {
    Movable::move(dt);
    if (animate) {
      spriteUpdate(dt);
    }
    Movable::translate(transx, transy);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->img);
    SDL_RenderCopy(renderer, texture, &(this->spriteSheetRect), &(this->rect));
 //   Movable::setAir(false);
    if(hasGrav && !onGround){
      this->gravity = 1;
    }
}

void Movable::spriteUpdate(int dt) {
    if (this->timeSinceSpriteChange >= 80) {
        this->spriteSheetRect.x += this->spriteSheetRect.w;
        if (this->spriteSheetRect.x >= sheetWidth) {
            this->spriteSheetRect.x = 0;
        }
        this->timeSinceSpriteChange = 0;
    }
    this->timeSinceSpriteChange += dt;
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
        Movable::setVelY(-10);
    }
}

SDL_Rect* Movable::getRect() {
    return &(this->rect);
}

int Movable::getReallyRectX(){
  return this->truex;
}

int Movable::getReallyRectY(){
  return this->truey;
}

SDL_Rect * Movable::getTrueRect() {
  this->truerect.x = this->truex;
  this->truerect.y = this->truey;
  return &(this->truerect);
}

void Movable::setAir(bool b) {
  this->inAir = b;
}
bool Movable::getAir() {
  return this->inAir;
}
void Movable::setRect(int x, int y, int w, int h) {
  SDL_Rect newrect= {x,y,w,h};
  this->truerect = newrect;
  this->rect = newrect;
  /*
  this->rect.x = x;
  this->rect.y = y;
  this->rect.w = w;
  this->rect.h = h;*/
}

void Movable::setGravity(int x){

  this->gravity = x;

}
void Movable::setLeftBound(int x) {
  this->leftBound = x;
  std::cout << "set left bound " << x << std::endl;
}
void Movable::setRightBound(int x) {
  this->rightBound = x;
  std::cout << "set right bound " << x << std::endl;
}
void Movable::setUpperBound(int x) {
  this->upperBound = x;
  std::cout << "set upper bound " << x << std::endl;
}
void Movable::setLowerBound(int x) {
  this->lowerBound = x;
  std::cout << "set lower bound " << x << std::endl;
}
