#include "LevelEditor.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

LevelEditor::LevelEditor() {}

LevelEditor::~LevelEditor() {}

LevelEditor::LevelEditor(string fileName) {

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
    char move; //Y or N
    int min; //minimum moving bounds. -1 if not moving between.
    int max; //maximum moving bounds. -1 if not moving between.
    bool animate;
    Movable temp;
    AutoMovable autoTemp;

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
        case 'G':
            temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, width, height, false, animate);
            this->ground.push_back(temp);
            break;
        case 'P':
            inFile >> move;
            inFile >> min;
            inFile >> max;
            if(move == 'Y') {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, false, animate);
                autoTemp.setMoveBounds(min,max);
            } else {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, true, animate);
            }
            this->pit.push_back(autoTemp);
            break;
        case 'E':
            inFile >> move;
            inFile >> min;
            inFile >> max;
            if(move == 'Y') {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, false, animate);
                autoTemp.setMoveBounds(min,max);
            } else {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, true, animate);
            }
            this->enemies.push_back(autoTemp);
            break;
        case 'D':
            temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false, animate);
            this->door = temp;
            break;
        }
    }

    //inFile.close();
}
