/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include "Movable.h";
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
using std::string;

#ifndef _CAMERA_H
#define _CAMERA_H

class Camera {

public:
    Camera();
    Camera(int levelWidth, int levelHeight, int x, int y, int w, int h);
    ~Camera();
    void center(int x, int y);
};

#endif
