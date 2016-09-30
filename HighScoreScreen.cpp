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
#include <vector>
#include "HighScoreScreen.h"
#include "Movable.h"
#include "AutoMovable.h"
#include "Screen.h"

using namespace std;

  vector<const char *> scores;
  vector<SDL_Surface*> scoresurfaces;
vector<SDL_Texture*> scoretex;
  vector<SDL_Rect> scorerect;
  SDL_Color textcolor = {0,0,0,255};
  SDL_Surface * titlesurface;
  SDL_Texture *titletex;
  SDL_Rect titleRect;
  TTF_Font *TitleFont;
  TTF_Font *ScoresFont;
const char* ScoreTitle = "SWAG SCORES";
const char*  name = "SMP: 9000";
HighScoreScreen::HighScoreScreen(){}

HighScoreScreen::HighScoreScreen(SDL_Renderer * renderer){
  
  /**Load in the high scores here. */
  for(int x = 0; x < 5; x++){

    scores.push_back(name);

  }
  
  TTF_Init();
  TitleFont = TTF_OpenFont("8bit.ttf", 72);
  ScoresFont = TTF_OpenFont("8bit.ttf", 24);
  titlesurface = TTF_RenderUTF8_Blended(TitleFont, ScoreTitle, textcolor);
  titletex = SDL_CreateTextureFromSurface(renderer, titlesurface);
  titleRect = {100, 0, 600, 75};
  for(int x = 0; x < 5; x++){
    scoresurfaces.push_back(TTF_RenderUTF8_Blended(ScoresFont, scores[x], textcolor));
    scoretex[x] = SDL_CreateTextureFromSurface(renderer, scoresurfaces[x]);
    scorerect[x] = {150, (75+75*x), 500, 75};
  }

}

HighScoreScreen::~HighScoreScreen(){

  TTF_Quit();

}

//return ints for to determine which screen to switch to

int HighScoreScreen::input(SDL_Event * event, int dt){

switch (event->type) {
  case SDL_KEYUP:
    if(event->key.keysym.sym == SDLK_SPACE) {
	return 1;
    }
    break;
  }
  return 0;
}

void HighScoreScreen::draw(SDL_Renderer * renderer, int dt){
  SDL_RenderCopy(renderer,titletex,NULL,&(titleRect));
  for(int x = 0; x < 5; x++){

    SDL_RenderCopy(renderer,scoretex[x],NULL,&(scorerect[x]));

  }
}
