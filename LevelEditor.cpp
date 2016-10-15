#include <iostream>
#include <fstream>
#include <string>
#include "LevelEditor.h"

using namespace std;

LevelEditor::LevelEditor(){}

LevelEditor::~LevelEditor(){}

LevelEditor::LevelEditor(string fileName) {
	
    ifstream inFile;
	inFile.open(fileName);
	
	if(inFile.fail()) {
		cerr << "Error Opening File" << endl;
		exit(1);
	}
	

    
	char code;
    string init;
    const char * imageName;
    int x;
    int y;
    int width;
    int height;
    Movable temp;
    


    inFile >> this->levelWidth;
    inFile >> this->levelHeight;

	while (!inFile.eof()) {
		inFile >> code;
        inFile >> x;
        inFile >> y;    
        inFile >> width;
        inFile >> height;
        inFile >> init;
        imageName = init.c_str();

        switch (code) {
            case 'G': 
	      temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 100, 100, false,false);
                this->ground.push_back(temp);       
            case 'P':
	      temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, true,false);
                this->pit.push_back(temp);
            case 'E':
	      temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, true,false);
                this->enemies.push_back(temp);
            case 'D':
	      temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false,false);
                this->door = temp;
        }
 
	}

	inFile.close();
}
