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
#include <string>
using std::string;

#ifndef _HELPER_H
#define _HELPER_H

class Helper : public Movable {
  int initX;
  int initY;
 public:
  Helper();
  Helper(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetW, int sheetH)
    : Movable(fileName, width, height, cornerX, cornerY, levelWidth, levelHeight, sheetW, sheetH) {
    initX = cornerX;
    initY = cornerY;
  };
  Helper(const char* fileName, int width, int height, int cornerX, int cornerY, int levelWidth, int levelHeight, int sheetW, int sheetH, bool hasGravity, bool anim)
    : Movable(fileName, width, height, cornerX, cornerY, levelWidth, levelHeight, sheetW, sheetH, hasGravity, anim) {
    initX = cornerX;
    initY = cornerY;
  };
  ~Helper();
  int getInitX();
  int getInitY();
 private:
};

#endif
