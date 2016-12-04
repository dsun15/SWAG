#include "LevelEditor.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

LevelEditor::LevelEditor() {
    this->enemies = new vector<AutoMovable>();
    this->enemies->reserve(30);
    this->pit = new list<AutoMovable>();
    this->ground = new list<AutoMovable>();
    this->helpers = new list<Movable*>();
    this->text = new list<Movable *>();
}

LevelEditor::~LevelEditor() {
    this->enemies->clear();
    this->ground->clear();
    this->pit->clear();
    delete this->enemies;
    delete this->pit;
    delete this->ground;
    while (!this->helpers->empty()) {
        delete this->helpers->front();
        this->helpers->pop_front();
    }
    delete this->helpers;
    while (!this->text->empty()) {
      delete this->text->front();
      this->text->pop_front();
    }
    delete this->text;
}

void LevelEditor::read(string fileName) {
    enemies->clear();
    ground->clear();
    pit->clear();
    while (!this->helpers->empty()) {
        delete this->helpers->front();
        this->helpers->pop_front();
    }
    while (!this->text->empty()) {
      delete this->text->front();
      this->text->pop_front();
    }

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
    //int spriteWidth;
    //int spriteHeight;
    int frames;

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

        switch (code) {
        case 'G': {
            inFile >> init;
            imageName = init.c_str();
            inFile >> move;
            inFile >> min;
            inFile >> max;
            AutoMovable tempg(AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, width, height, false, animate));
            if (animate) {
                tempg.setMoveBounds(min, max);
            }
            this->ground->push_back(tempg);
            tempg.prepFree();
            break;
        }
        case 'P': {
            inFile >> init;
            imageName = init.c_str();
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
            inFile >> init;
            imageName = init.c_str();
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
            inFile >> init;
            imageName = init.c_str();
            Movable doort(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false, animate);
            this->door = doort;
            doort.prepFree();
            break;
        }
        case 'H': {
            inFile >> init;
            imageName = init.c_str();
            //inFile >> spriteWidth;
            //inFile >> spriteHeight;
            inFile >> frames;
            Movable* help = new Helper(imageName, width, height, x, y, this->levelWidth, this->levelHeight, x * frames, y, true, animate);
            this->helpers->push_back(help);
            break;
        }
        case 'T': {
            //string temp;
           // init = "";
            //while (!inFile.eof()) {
              //  inFile >> temp;
                //init = init + temp + " ";
           // }
            getline(inFile, init);
            //cout << init <<endl;
	    const auto strBegin = init.find_first_not_of(" \n");
	    const auto strEnd = init.find_last_not_of(" \n");
	    init = init.substr(strBegin, strEnd - strBegin +1);
	    //cout << init << endl;
            imageName = init.c_str();
	    //cout << imageName << endl;
            Movable * textt = new Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, x, y, false, animate);
            //cout << textt->getName() << endl;
            this->text->push_back(textt);
	    //cout << this->text->back()->getName();
            //textt.prepFree();
	    inFile >> code;
            break;
        }
        }
    }

    inFile.close();
}
