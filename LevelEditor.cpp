#include "LevelEditor.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

LevelEditor::LevelEditor() {
    this->enemies = new vector<AutoMovable>();
    this->enemies->reserve(30);
    this->pit = new list<AutoMovable>();
    this->ground = new list<Movable>();
}

LevelEditor::~LevelEditor() {
    this->enemies->clear();
    this->ground->clear();
    this->pit->clear();
    delete this->enemies;
    delete this->pit;
    delete this->ground;
}

void LevelEditor::read(string fileName) {
    enemies->clear();
    ground->clear();
    pit->clear();
    ifstream inFile;
    inFile.open(fileName);

    if (inFile.fail()) {
        cerr << "Error Opening File" << endl;
        exit(1);
    }

    char code;
    string init;
    const char* imageName;
    int x;
    int y;
    int width;
    int height;
    bool move;
    int min; //minimum moving bounds. -1 if not moving between.
    int max; //maximum moving bounds. -1 if not moving between.
    bool animate;

    inFile >> this->levelWidth;
    inFile >> this->levelHeight;
    inFile >> playerInitX;
    inFile >> playerInitY;

    while (!inFile.eof()) {
        inFile >> code;
        inFile >> animate;
        inFile >> x;
        inFile >> y;
        inFile >> width;
        inFile >> height;
        inFile >> init;
        imageName = init.c_str();

        switch (code) {
        case 'G': {
            Movable tempg(Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, width, height, false, animate));
            this->ground->push_back(tempg);
            tempg.prepFree();
            break;
        }
        case 'P': {
            inFile >> move;
            inFile >> min;
            inFile >> max;
            AutoMovable tempp(AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 550, 50, !move, animate));
            if (move) {
                tempp.setMoveBounds(min, max);
            }
            this->pit->push_back(tempp);
            tempp.prepFree();
            break;
        }
        case 'E': {
            inFile >> move;
            inFile >> min;
            inFile >> max;
            AutoMovable tempe(AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 550, 50, !move, animate));
            if (move) {
                tempe.setMoveBounds(min, max);
            }
            this->enemies->push_back(tempe);
            tempe.prepFree();
            break;
        }
        case 'D': {
            Movable doort(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false, animate);
            this->door = doort;
            doort.prepFree();
            break;
        }
        }
    }

    inFile.close();
}
