#include "LevelEditor.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

LevelEditor::LevelEditor() {}

LevelEditor::~LevelEditor() {}

void LevelEditor::read(string fileName) {
    enemies.clear();
    ground.clear();
    pit.clear();
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
    //char move; //Y or N
    bool move;
    int min; //minimum moving bounds. -1 if not moving between.
    int max; //maximum moving bounds. -1 if not moving between.
    bool animate;
    //Movable temp;
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
            this->ground.push_back(Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, width, height, false, animate));
            //this->ground.push_back(temp);
            break;
        case 'P':
            inFile >> move;
            inFile >> min;
            inFile >> max;
	    this->pit.push_back(AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, !move, animate));
            if(move) {
	      this->pit.back().setMoveBounds(min,max);
	    }
	      /*
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, false, animate);
                autoTemp.setMoveBounds(min,max);
            } else {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, true, animate);
		}*/
            this->pit.push_back(autoTemp);
            break;
        case 'E':
            inFile >> move;
            inFile >> min;
            inFile >> max;
	    this->enemies.push_back(AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, !move, animate));
            if(move) {
	      //autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, false, animate);
	      //autoTemp.setMoveBounds(min,max);
	      this->enemies.back().setMoveBounds(min,max);
	    }
		/*} else {
                autoTemp = AutoMovable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 300, 50, true, animate);
		}*/
            this->enemies.push_back(autoTemp);
            break;
        case 'D':
            this->door = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false, animate);
            break;
        }
    }

    inFile.close();
}
