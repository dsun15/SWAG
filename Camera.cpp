/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include "Movable.h"
#include "Camera.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
using std::string;

Camera::Camera() {
    this->gravity = 0;
}

Camera::Camera(int levelWidth, int levelHeight, int x, int y, int w, int h) {
    this->gravity = 0;
    this->levelWidth = levelWidth;
    this->levelHeight = levelHeight;
    this->rect = {x, y, w, h};
}    

Camera::~Camera() {}

void Camera::center(int x, int y){
    this->rect.x = (x - (this->rect.w / 2));
    if (this->rect.x < 0 ) {
        this->rect.x = 0;
    }
    if (this->rect.x > this->levelWidth)
      this->rect.x = this->levelWidth - this->rect.w;
    if (this->rect.y < 0)
      this->rect.y = 0;
    if (this->rect.y > this->levelHeight)
      this->rect.y = this->levelHeight - this->rect.h;
    this->rect.y = (y - (this->rect.h / 2));
}
