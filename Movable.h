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

	const char * fileName;
	protected: int windowW; //x axis
	protected: int windowH; //y axis
	protected: SDL_Rect rect;
	protected: SDL_Surface* img; 
public:
	Movable(); 
	
	Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH);

	Movable(const Movable&);

	~Movable(); 

	void move(int x, int y);

	bool checkCollide(Movable *m);
	
	void draw(SDL_Renderer * renderer);

private:

};	

#endif
