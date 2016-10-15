#include <iostream>
#include <fstream>
#include <string>

using namespace std;
class LevelEditor {

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
        inFile >> imageName;

        switch (code) {
            case 'G': 
                temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false);
                this->ground.push_back(temp);       
            case 'P':
                temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, true);
                this->pit.push_back(temp);
            case 'E':
                temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, true);
                this->enemy.push_back(temp);
            case 'D':
                temp = Movable(imageName, width, height, x, y, this->levelWidth, this->levelHeight, 50, 50, false);
                this->door = temp;
        }
 
	}

	inFile.close();

}
