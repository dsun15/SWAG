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
    this->spriteSheetRect = { 0, 0, 50, 50 };
    this->sheetWidth = sheetWidth;
    this->sheetHeight = sheetHeight;
    this->truex = cornerX;
    this->truey = cornerY;
}

Movable::Movable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetWidth, int sheetHeight, bool hasGravity) {
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
    this->spriteSheetRect = { 0, 0, 50, 50 };
    this->sheetWidth = sheetWidth;
    this->sheetHeight = sheetHeight;
    if (!hasGravity)
        this->gravity = 0;
    this->truex = cornerX;
    this->truey = cornerY;
}

Movable::Movable(const Movable& m) {
    this->fileName = m.fileName;
    this->levelWidth = m.levelWidth;
    this->levelHeight = m.levelHeight;
    this->rect = m.rect;
    this->img = IMG_Load(fileName);
    this->truex = m.truex;
    this->truey = m.truey;
}

Movable::~Movable() {
}

void Movable::accelerate(int dt, int accX) {
    this->velX = this->velX + accX * dt;
    this->velY = this->velY + this->gravity * (dt / 2);
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
        if (this->velX > 0) {
            Movable::accelerate(dt, -1);
        }
        if (this->velX < 0) {
            Movable::accelerate(dt, 1);
        }
    }
    Movable::accelerate(dt, 0);

    //checking for boundary collisions
    if (this->rect.x < 0) {
        this->rect.x = 0;
        this->velX = 0;
    }
    if (this->rect.y < 0) {
        this->rect.y = 0;
        this->velY = 0;
    }
    if (this->rect.x + this->rect.w > levelWidth
) {
        this->rect.x = levelWidth
 - this->rect.w;
        this->velX = 0;
    }
    if (this->rect.y + this->rect.h > levelHeight) {
        this->rect.y = levelHeight - this->rect.h;
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
    if (this->rect.x < 0) {
        this->rect.x = 0;
    }
    if (this->rect.y < 0) {
        this->rect.y = 0;
    }
    if (this->rect.x + this->rect.w > levelWidth
) {
        this->rect.x = levelWidth - this->rect.w;
    }
    if (this->rect.y + this->rect.h > levelHeight) {
        this->rect.y = levelHeight - this->rect.h;
        this->inAir = false;
    }

    this->truex = this->rect.x;
    this->truey = this->rect.y;
}

void Movable::translate(int x, int y) {
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
    if (this->rect.x + this->rect.w > levelWidth
) {
        this->rect.x = levelWidth - this->rect.w;
    }
    if (this->rect.y + this->rect.h > levelHeight) {
        this->rect.y = levelHeight - this->rect.h;
        this->inAir = false;
    }

}

bool Movable::checkCollide(Movable* m) {
    const SDL_Rect* r1 = &(this->rect);
    const SDL_Rect* r2 = &(m->rect);
    return SDL_HasIntersection(r1, r2);
}

bool Movable::checkCollide(SDL_Rect* rect) {
    const SDL_Rect* temp = &(this->rect);
    return SDL_HasIntersection(temp, rect);
}

void Movable::draw(SDL_Renderer* renderer, int dt, int transx, int transy) {
    Movable::move(dt);
    spriteUpdate(dt);
    Movable::translate(transx, transy);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, this->img);
    SDL_RenderCopy(renderer, texture, &(this->spriteSheetRect), &(this->rect));
}

void Movable::spriteUpdate(int dt) {
    if (this->timeSinceSpriteChange >= 80) {
        this->spriteSheetRect.x += 50;
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
        Movable::setVelY(-8);
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
