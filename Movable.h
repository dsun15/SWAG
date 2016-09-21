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

#ifndf _MOVABLE_H
#define _MOVABLE_H

class Movable() {

	str fileName;
	int width;
	int height;
	int cornerX;
	int cornerY;
	int windowW; //x axis
	int windowH; //y axis
	SDL_Rect rect;

	Movable(); 
	
	Movable(str fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH);

	Movable(const Movable&);

	~Movable(); 

	void move(int x, int y);

	bool checkCollide(Movable *m);

}	

#endif
