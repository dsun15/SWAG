#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <string>
#include <list>

using std::string;

#ifndef  _LEVELEDITOR_H
#define _LEVELEDITOR_H

class LevelEditor {

public:
    std::list<Movable> ground;
    std::list<Movable> enemies;
    std::list<Movable> pit;
    Movable door;
    int levelWidth;
    int levelHeight;

    LevelEditor();
    ~LevelEditor();
    



};

#endif
