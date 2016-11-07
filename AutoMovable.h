/**
 * S.W.A.G.
 * Chris, Devin, Kevin, William
 * 600.255 Intro to Video Game Design
 */

#include "Movable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
using std::string;

#ifndef _AUTOMOVABLE_H
#define _AUTOMOVABLE_H

class AutoMovable : public Movable {
    char dir;
    bool isAlive=true;
public:
    AutoMovable();
    AutoMovable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetW, int sheetH)
        : Movable(fileName, width, height, cornerX, cornerY, levelWidth, levelHeight, sheetW, sheetH) {
        srand(time(NULL));
        this->MAX_HORIZ = 1;
	this->isAlive = true;
    };
    AutoMovable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetW, int sheetH, bool hasGravity, bool anim)
        : Movable(fileName, width, height, cornerX, cornerY, levelWidth, levelHeight, sheetW, sheetH, hasGravity, anim) {
        srand(time(NULL));
        this->MAX_HORIZ = 1;
	this->isAlive = true;
    };
    ~AutoMovable();
    void automove(int time);
    void moveBetween(int minCoor, int maxCoor, int dt);
    void genDir();
    void move(int x, int y);
    void setLife(bool isAlive);
    bool getLife();

private:
};

#endif
