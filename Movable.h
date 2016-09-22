/*
* S.W.A.G. 
* Chris, Devin, Kevin, William 
* 600.255 Intro to Video Game Design
*
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using std::string;

#ifndef _MOVABLE_H
#define _MOVABLE_H

class Movable {

	string fileName;
	int width;
	int height;
	int cornerX;
	int cornerY;
	int windowW; //x axis
	int windowH; //y axis
	SDL_Rect rect;

public:
	Movable(); 
	
	Movable(string fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH);

	Movable(const Movable&);

	~Movable(); 

	void move(int x, int y);

	bool checkCollide(Movable *m);
	
	void draw(SDL_Renderer * renderer);

private:

};	

#endif
