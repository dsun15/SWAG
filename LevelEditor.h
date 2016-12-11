#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "Movable.h"
#include "AutoMovable.h"
#include "Helper.h"
using std::string;

#ifndef  _LEVELEDITOR_H
#define _LEVELEDITOR_H

class LevelEditor {

public:
    std::list<AutoMovable *> * ground;
    std::vector<AutoMovable *> * enemies;
    std::list<AutoMovable *> * pit;
    std::list<Movable *> * helpers;
    std::list<Movable *> * text;
    int playerInitX;
    int playerInitY;
    Movable * door = NULL;
    int levelWidth;
    int levelHeight;

    LevelEditor();
    ~LevelEditor();
    void read(string s);
};

#endif
