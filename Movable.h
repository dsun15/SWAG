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
 protected: int timeSinceSpriteChange;
 protected: SDL_Rect spriteSheetRect;
 protected: int sheetWidth;
 protected: int sheetHeight;
public:
	Movable(); 
	
	Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH, int sheetWidth, int sheetHeight);

	Movable(const Movable&);

	~Movable();

	void inputMove(int dt, int direction); 

	void move(int x, int y);

	bool checkCollide(Movable *m);
	
	void draw(SDL_Renderer * renderer, int dt);
	
	void spriteUpdate(int dt);

private:

};	

#endif
