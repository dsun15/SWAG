/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

using std::string;

#ifndef _MOVABLE_H
#define _MOVABLE_H

class Movable {


protected:
    const char* fileName;
    double MAX_HORIZ = 2;
    double MAX_VERT = 2;
    double gravity = 1;
    int levelWidth; //x axis
    int levelHeight; //y axis
    double velX = 0;
    double velY = 0;
    SDL_Rect rect;
    SDL_Surface* img;
    int timeSinceSpriteChange;
    SDL_Rect spriteSheetRect;
    int sheetWidth;
    int sheetHeight;
    bool inAir = false;
    bool isMoving = false;
    bool alive = true;
    //true laction
    int truex;
    int truey;
    SDL_Rect truerect;
    bool animate;
    bool hasGrav = true;
    int leftBound;
    int rightBound;
    int upperBound;
    int lowerBound;
    int minMoveBound = 0;
    int maxMoveBound = 0;
    bool stackedMove = false;
    int stacked = -1;
    bool isJumping = false;
    int jumpTime = 0;
public:
    Movable();

    Movable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetWidth, int sheetHeight);

    //somewhat sloppy to keep both, but don't need to change as many files this way
    Movable(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetWidth, int sheetHeight, bool hasGravity, bool anim);

    //Movable(const Movable&);

    ~Movable();

    void accelerate(int dt, double accX, double accY);

    void move(int dt);

    void move(int x, int y);

    void translate(int x, int y);

    bool checkCollide(Movable* m);

    bool checkCollide(SDL_Rect*);

    void draw(SDL_Renderer* renderer, int dt, int transx, int transy, bool onGround);

    void spriteUpdate(int dt);
    void setMove(bool);
    void setVelX(int n);
    void setVelY(int n);
    SDL_Rect* getRect();
    int getReallyRectX();
    int getReallyRectY();
    SDL_Rect * getTrueRect();
    void setAir(bool);
    bool getAir();
    bool getGravity();
    void jump();
    void setRect(int x, int y, int w, int h);
    void setGravity(int x);
    void setLeftBound(int x);
    void setRightBound(int x);
    void setUpperBound(int x);
    void setLowerBound(int x);
    int getLowerBound();
    int getUpperBound();
    void setMoveBounds(int min, int max);
    int getMinMoveBound();
    int getMaxMoveBound();
    void moveBetween(int dt);
    void setStacked(int x);
    void setStackedMove(bool z);
    int getStacked();
    bool getStackedMove();
    void prepFree();
private:
};

#endif
