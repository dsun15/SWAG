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

protected:
	int MAX_HORIZ = 3;
	int MAX_VERT = 3;
	int gravity = 1;
	int windowW; //x axis
	int windowH; //y axis
	int velX=0;
	int velY=0;
	SDL_Rect rect;
	SDL_Surface* img; 
	int timeSinceSpriteChange;
 	SDL_Rect spriteSheetRect;
 	int sheetWidth;
 	int sheetHeight;
	bool inAir = false;
	bool isMoving = false;
public:
	Movable(); 
	
	Movable(const char * fileName, int width, int height, int cornerX, int cornerY, int windowW, int windowH, int sheetWidth, int sheetHeight);

	Movable(const Movable&);

	~Movable();

	void accelerate(int dt, int accX); 

	void move(int dt);

	void move(int x, int y);

	bool checkCollide(Movable *m);

	bool checkCollide(SDL_Rect *);
		
	void draw(SDL_Renderer * renderer, int dt);
	
	void spriteUpdate(int dt);
	void setMove(bool);
	void setVelX(int n);
	void setVelY(int n);
	void jump();
private:

};	

#endif
