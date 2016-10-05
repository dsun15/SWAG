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
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include "HighScoreScreen.h"
#include "Movable.h"
#include "AutoMovable.h"
#include "Screen.h"

using namespace std;
string name = "SMP: 9000";
const char* ScoreTitle = "SWAG SCORES";

/*vector<string> scores(5,name);
vector<SDL_Surface *> scoresurfaces;
vector<SDL_Texture *> scoretex;
vector<SDL_Rect> scorerect;*/
SDL_Surface * scoresurfaces[5];
SDL_Texture * scoretex[5];
SDL_Rect scorerect[5];

SDL_Color textcolor = {255,255,255,255};
SDL_Surface * titlesurface;
SDL_Texture * titletex;
SDL_Rect titleRect;
TTF_Font * TitleFont;
TTF_Font * ScoresFont;
//const char* ScoreTitle = "SWAG SCORES";
//string name = "SMP: 9000";

HighScoreScreen::HighScoreScreen(){}

HighScoreScreen::HighScoreScreen(SDL_Renderer * renderer){
  filename = "scores.txt";
  ifstream scores_file(filename);
  string temp;

  if(scores_file.is_open()){
    /**Load in the high scores here. */
    for(int x = 0; x < 5; x++){
      if(getline(scores_file, temp)){
	names[x] = temp;
	getline(scores_file, temp);
	scores[x] = stoi(temp);
      }
    }
  }
  //cout << scores.size();
  TTF_Init();
  TitleFont = TTF_OpenFont("8bit.ttf", 72);
  ScoresFont = TTF_OpenFont("8bit.ttf", 24);
  titlesurface = TTF_RenderUTF8_Blended(TitleFont, ScoreTitle, textcolor);
  titletex = SDL_CreateTextureFromSurface(renderer, titlesurface);
  titleRect = {100, 25, 300, 50};
  for(int x = 0; x < 5; x++){
    stringstream score_build;
    score_build << names[x] << "  "  << to_string(scores[x]);
    string tmp_scr;
    tmp_scr = score_build.str();
    const char * tempstr = tmp_scr.c_str();
    SDL_Surface * temp =  TTF_RenderUTF8_Blended(ScoresFont,tempstr,textcolor);
    scoresurfaces[x] = temp;
    //scoresurfaces.push_back(temp);
    //scoresurfaces.push_back(TTF_RenderUTF8_Blended(ScoresFont, scores[x], textcolor));
    scoretex[x] = SDL_CreateTextureFromSurface(renderer, scoresurfaces[x]);
    scorerect[x] = {150, (100+75*x), 300, 50};
  }

}

HighScoreScreen::~HighScoreScreen(){
  //TTF_Quit();
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
