/* 
* S.W.A.G.
* Chris, Devin, Kevin, William
* 600.255 Intro to Video Game Design
*
*/

#include "AutoMovable.h"
#include "Movable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;
using std::string;

int timeSinceChange = 0;

AutoMovable::AutoMovable() {}

AutoMovable::~AutoMovable() {}

void AutoMovable::automove(int time) {
    //for time based movement
    if (timeSinceChange >= 2000) {
        int percent = rand() % 100;
        if (percent <= 50) {
            AutoMovable::genDir();
        }
        timeSinceChange = 0;
    }
    int speed = time / 3;
    switch (this->dir) {
    case 'N':
        // AutoMovable::move(0,-1*speed);
        break;
    case 'E':
        AutoMovable::move(speed, 0);
        break;
    case 'S':
        //AutoMovable::move(0,speed);
        break;
    case 'W':
        AutoMovable::move(-1 * speed, 0);
        break;
    default:
        //	AutoMovable::genDir();
        break;
    }
    if (this->rect.x == 0) {
        this->dir = 'E';
        timeSinceChange = '0';
    } else if (this->rect.y == 0) {
        this->dir = 'S';
        timeSinceChange = '0';
    } else if (this->rect.x + this->rect.w >= levelWidth) {
        this->dir = 'W';
        timeSinceChange = '0';
    } else if (this->rect.y + this->rect.h >= levelHeight) {
        this->dir = 'N';
        timeSinceChange = '0';
    }
    timeSinceChange += time;
}

void AutoMovable::move(int x, int y) {
    x++;
    y++;
}

void AutoMovable::moveBetween(int minCoor, int maxCoor, int dt) {
    if (!(this->isMoving)) {
        Movable::accelerate(dt, 1, 0);
        Movable::setMove(true);
    }
    if (this->isMoving) {
        if ((this->truex + Movable::getRect()->w) >= maxCoor) {
            Movable::setVelX(0);
            Movable::accelerate(dt, -1, 0);
            Movable::move(dt / 4);
        } else if ((this->truex) <= minCoor) {
            Movable::setVelX(0);
            Movable::accelerate(dt, 1, 0);
            Movable::move(dt / 4);
        }
    }
}

void AutoMovable::genDir() {
    int temp;
    temp = rand() % 4;
    switch (temp) {
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

void AutoMovable::setLife(bool isAlive) {
    this->isAlive = isAlive;
}

bool AutoMovable::getLife() {
    return this->isAlive;
}
