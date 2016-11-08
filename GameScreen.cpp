/*
* S.W.A.G.
* Chris, Devin, Kevin, William
* 600.255 Intro to Video Game Design
*
*/

#include "GameScreen.h"
#include "AutoMovable.h"
#include "Camera.h"
#include "LevelEditor.h"
#include "Movable.h"
#include "Screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;
int width = 1000;
int height = 600;
//SDL_Texture* gTexture;
//SDL_Texture* gTexture2;
Movable door;
const int MAX_LV = 3;
//AutoMovable enemy;
bool gameOver = false;
bool youWin = false;
bool play[] = { true, true, true, true, true };
Mix_Chunk* sfx;
Mix_Chunk* sfxJump;
int option;
Mix_Music* music;
const char* musicName = "levelOne.ogg";
const char* effect = "bump.ogg";
const char* jumpEffect = "jump.ogg";
const char* win = "You win";
const char* lose = "You lose";
const char* cont = "Press Enter To Continue";
SDL_Texture* wintext;
SDL_Texture* losetext;
SDL_Texture* continuetext;
SDL_Texture* scoretext;
SDL_Texture* lifetext;
SDL_Texture* background[MAX_LV];
SDL_Texture* spriteLives;
SDL_Rect winrect = { 400, 50, 300, 50 };
SDL_Rect loserect = { 400, 50, 300, 50 };
SDL_Rect continuerect = { 100, 125, 600, 50 };
SDL_Rect gamescorerect = { 50, 50, 75, 50 };
SDL_Rect lifecountrect = { 725, 525, 75, 50 };
SDL_Rect backrect = { 0, 0, 800, 600 };
SDL_Rect livesRect = { 650, 534, 40, 40 };
int wlswitch; // 1 = win, 2 = lose
int score;
TTF_Font* gamefont;
bool scorewritten = false;
Camera camera;
int lives;
int playerNum = 0;

int levelnum = 1;
string levelfile;
//string levelfile = "level2A.txt";
LevelEditor level; // = LevelEditor(levelfile);
std::vector<Movable> playables;

std::list<Movable>* ground;
//std::vector<AutoMovable>* enemies = new vector<AutoMovable>;
std::vector<AutoMovable>* enemies;
std::list<AutoMovable>* pit;

SDL_Surface* bs[MAX_LV]; /* = IMG_Load("BackgroundGradient1.png");*/
SDL_Surface* jibby = IMG_Load("jibbyOneFrame.png");

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer* renderer) {
    //set starting lives
    lives = 5;

    //Level Stuff
    //level = LevelEditor("level1.txt");
    //level = LevelEditor("level2A.txt");
    levelfile = "level" + to_string(levelnum) + ".txt";
    //level = LevelEditor(levelfile);
    level.read(levelfile);
    //level.read("level2B.txt");
    width = level.levelWidth;
    height = level.levelHeight;
    //    SDL_Surface* bs = IMG_Load("BackgroundGradient.png");
    for (int i = 0; i<MAX_LV; i++) {
      string backfile = "BackgroundGradient" + to_string(i+1) + ".png";
      bs[i] = IMG_Load(backfile.c_str());
      background[i] = SDL_CreateTextureFromSurface(renderer,bs[i]);
    }
    //background[0] = SDL_CreateTextureFromSurface(renderer, bs);
    spriteLives = SDL_CreateTextureFromSurface(renderer, jibby);
    //    SDL_FreeSurface(bs);
    //Player, Camera
    camera = Camera(level.levelWidth, level.levelHeight, 0, 0, 800, 600);

    Movable jibby("jibbyidle.png", 50, 50, 0, 0, width, height, 600, 50);
    //Movable jibby2("jibbyidle.png", 50, 50, 0, 0, width, height, 600, 50);

    playables.emplace_back(jibby);
    //playables.emplace_back(jibby2);
    jibby.prepFree();
    //jibby2.prepFree();


    //Objects from level file
    ground = level.ground;
    enemies = level.enemies;
    pit = level.pit;

    //test enemy
    //  enemy = AutoMovable("enemy1.png", 50, 50, 2000, 450, width, height, 300, 50, false, true);

    door = level.door;
    level.door.prepFree();
    //Audio Stuff
    Mix_HaltChannel(1);
    Mix_Resume(1);
    if (!Mix_PausedMusic()) {
        Mix_SetMusicCMD("ogg123");
        music = Mix_LoadMUS(musicName);
        Mix_PlayMusic(music, -1);
    } else {
        Mix_ResumeMusic();
    }
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    sfx = Mix_LoadWAV(effect);
    sfxJump = Mix_LoadWAV(jumpEffect);

    gameOver = false;
    youWin = false;

    //Text Stuff
    //TTF_Init();
    gamefont = TTF_OpenFont("8bit.ttf", 72);
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* ws = TTF_RenderUTF8_Blended(gamefont, win, white);
    SDL_Surface* ls = TTF_RenderUTF8_Blended(gamefont, lose, white);
    SDL_Surface* cm = TTF_RenderUTF8_Blended(gamefont, cont, white);
    wintext = SDL_CreateTextureFromSurface(renderer, ws);
    losetext = SDL_CreateTextureFromSurface(renderer, ls);
    continuetext = SDL_CreateTextureFromSurface(renderer, cm);
    SDL_FreeSurface(ws);
    SDL_FreeSurface(ls);
    SDL_FreeSurface(cm);
    wlswitch = 0;
    score = 0;
    //Commandeering score writing to write lives
    scorewritten = false;

    return;
}

GameScreen::~GameScreen() {
    //ground->clear();
    //pit->clear();
    //enemies->clear();
    Mix_FreeMusic(music);
    Mix_FreeChunk(sfx);
    Mix_FreeChunk(sfxJump);
    SDL_DestroyTexture(wintext);
    SDL_DestroyTexture(losetext);
    SDL_DestroyTexture(continuetext);
    SDL_DestroyTexture(scoretext);
    SDL_DestroyTexture(lifetext);
    //SDL_DestroyTexture(background);
    SDL_DestroyTexture(spriteLives);
    //SDL_FreeSurface(bs);
    SDL_FreeSurface(jibby);
    TTF_CloseFont(gamefont);
    for (int i = 0; i<MAX_LV; i++) {
      SDL_FreeSurface(bs[i]);
      SDL_DestroyTexture(background[i]);
    }
}

int GameScreen::input(SDL_Event* event, int dt) {
    if (gameOver) {
        playables[playerNum].setVelX(0);
        std::ofstream inFile;
        inFile.open("scores.txt", std::ios_base::app);
        if (!scorewritten) {
            inFile << score << "\n";
            scorewritten = true;
        }
        if (event->key.keysym.sym == SDLK_RETURN) {
            if (levelnum == 3) {
                return 3;
            } else if (youWin == true) {
                GameScreen::advanceLevel();
            } else {
                GameScreen::hardReset();
            }
        }

    } else {
        switch (event->type) {
        case SDL_KEYUP:
            if (event->key.keysym.sym == SDLK_RIGHT) {
                playables[playerNum].setMove(false);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                playables[playerNum].setMove(false);
            }
            if (event->key.keysym.sym == SDLK_DOWN) {
            }
            if (event->key.keysym.sym == SDLK_UP) {
            }

            if (event->key.keysym.sym == SDLK_r) {
                GameScreen::advanceLevel();
            }
	    if (event->key.keysym.sym == SDLK_k) {
	      GameScreen::reset();
	    }
            if (event->key.keysym.sym == SDLK_TAB) {
                if (playerNum + 1 >= (int)playables.size()) {
                    playerNum = 0;
                } else {
                    playerNum++;
                }
            }
            break;

        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_RIGHT) {
                option = 3;
                playables[playerNum].accelerate(dt, 1, 0);
                playables[playerNum].setMove(true);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                option = 4;
                playables[playerNum].accelerate(dt, -1, 0);
                playables[playerNum].setMove(true);
            }
            if (event->key.keysym.sym == SDLK_DOWN) {
                option = 1;
            }
            if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP) {
                Mix_PlayChannel(-1, sfxJump, 1);
                option = 2;
	        if(!playables[playerNum].getAir())
		  playables[playerNum].accelerate(dt, 0, -2.5);
		//playables[playerNum].setAir(true);
                //playables[playerNum].jump();
            }
            break;
        }
    }
    return 0;
}

void GameScreen::draw(SDL_Renderer* renderer, int dt) {

  SDL_RenderCopy(renderer,background[levelnum-1],NULL,&backrect);

    SDL_Rect cameraLoc = *camera.getRect();
    bool playerOnGround = false;

    //this works
    camera.center(playables[playerNum].getReallyRectX(), playables[playerNum].getReallyRectY());
    if (door.checkCollide(camera.getRect())) {
        door.draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
    }
 
    for (int z = 0; z < (int) playables.size(); z++){
        playables[z].setUpperBound(0);
        playables[z].setLeftBound(0);
        playables[z].setRightBound(width);
        playables[z].setLowerBound(height + 100);

	playables[z].setStacked(-1);

    for (std::list<Movable>::iterator it = ground->begin(); it != ground->end(); ++it) {
        if ((*it).checkCollide(&cameraLoc)) {
            (*it).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
        }
        if (playables[z].checkCollide(&*it)) {
	  if (playables[z].getTrueRect()->y < (*it).getTrueRect()->y) {
                playerOnGround = true;

                playables[z].setLowerBound((*it).getTrueRect()->y + 1);
	  } else if (playables[z].getTrueRect()->y > (*it).getTrueRect()->y + (*it).getTrueRect()->h) {
	    playables[z].setUpperBound((*it).getTrueRect()->y + (*it).getTrueRect()->h);
	  }else if (playables[z].getTrueRect()->y >= (*it).getTrueRect()->y && playables[z].getTrueRect()->x < (*it).getTrueRect()->x) {
                playables[z].setRightBound((*it).getTrueRect()->x);
	  } else if (playables[z].getTrueRect()->y >= (*it).getTrueRect()->y && playables[z].getTrueRect()->x > (*it).getTrueRect()->x) {
                playables[z].setLeftBound((*it).getTrueRect()->x + (*it).getTrueRect()->w);
            }
        }
    }
 
    for(int x = 0; x < (int)playables.size(); x++){
      if (playables[x].checkCollide(playables[z].getTrueRect()) && z != x) {
	//std::cout << playerNum << "player player collision \n";
	if (playables[x].getTrueRect()->y < playables[z].getTrueRect()->y) {
                playerOnGround = true;
                playables[x].setLowerBound(playables[z].getTrueRect()->y + 1);
	} else if (playables[x].getTrueRect()->y > playables[z].getTrueRect()->y){
	      //There is someone on top, get ready to bring them with
	      playables[x].setUpperBound(playables[z].getTrueRect()->y+playables[z].getTrueRect()->h);
	      playerOnGround = false;
	      playables[z].setStacked(playerNum);
	}else if (playables[x].getTrueRect()->y >= playables[z].getTrueRect()->y && playables[x].getTrueRect()->x < playables[z].getTrueRect()->x) {
                playables[x].setRightBound(playables[z].getTrueRect()->x);
	} else if (playables[x].getTrueRect()->y >= playables[z].getTrueRect()->y && playables[x].getTrueRect()->x > playables[z].getTrueRect()->x) {
	      playables[x].setLeftBound(playables[z].getTrueRect()->x + playables[z].getRect()->w);
            }
        }
    }
    
    }

    //collision with enemies

    vector<AutoMovable>::iterator iter = enemies->begin();
    while (iter != enemies->end()) {
      //cout << enemies->size() << ": " << iter->getReallyRectX() << " " << iter->getReallyRectY() << endl;
        if (!((*iter).getGravity())) {
            (*iter).moveBetween((*iter).getMinMoveBound(), (*iter).getMaxMoveBound(), dt);
        }
        if ((*iter).getLife() /*(*iter).checkCollide(&cameraLoc)*/) {
            (*iter).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
        }
        if (playables[playerNum].checkCollide((*iter).getTrueRect()) && (*iter).getLife()) {
            if (playables[playerNum].getTrueRect()->y < (*iter).getTrueRect()->y) {
                //enemy kill;
                Mix_PlayChannel(-1, sfx, 1);
                playables[playerNum].setVelY(-4);

                score += 100;
                (*iter).setLife(false);
            } else {
	      iter = enemies->end();
              if (!gameOver) {GameScreen::reset();}
            }
	} else {
	  ++iter;
	}
    }
    //pits
    for (std::list<AutoMovable>::iterator it = pit->begin(), end = pit->end(); it != end; ++it) {
        //if no gravity, then it is moving between a bounds
        if (!((*it).getGravity())) {
            (*it).moveBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
        }
        (*it).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
        if (playables[playerNum].checkCollide((*it).getTrueRect())) {
	  //wlswitch = 2;
	  //gameOver = true;
	  if (!gameOver) {GameScreen::reset();}
            it = end;
        }
    }

    // enemy.moveBetween(1900, 2300, dt);
    // enemy.draw(renderer, dt, -cameraLoc.x, 0, true);
    for (int z = 0; z < (int)playables.size(); z++) {
        if (playables[z].checkCollide(&cameraLoc)) {
	  if(z == playerNum){
           playables[z].draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, playerOnGround);
	  }
	  else{
	    if(playables[z].getStacked() == playerNum){

	       playables[z].move(playables[playerNum].getTrueRect()->x - playables[z].getTrueRect()->x,
		 playables[playerNum].getTrueRect()->y - playables[z].getTrueRect()->y);
       	    playables[z].draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
	    
	    } else {

	      playables[z].draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
	      
	    }

	  }

        }
    }

    string temp = std::to_string(score);
    string life = std::to_string(lives);
    const char* temp2 = temp.c_str();
    const char* templife = life.c_str();
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* ss = TTF_RenderUTF8_Blended(gamefont, temp2, white);
    SDL_Surface* ls = TTF_RenderUTF8_Blended(gamefont, templife, white);
    scoretext = SDL_CreateTextureFromSurface(renderer, ss);
    lifetext = SDL_CreateTextureFromSurface(renderer, ls);
    SDL_RenderCopy(renderer, scoretext, NULL, &gamescorerect);
    SDL_RenderCopy(renderer, lifetext, NULL, &lifecountrect);
    SDL_RenderCopy(renderer, spriteLives, NULL, &livesRect);
    SDL_FreeSurface(ss);
    SDL_FreeSurface(ls);
    if (wlswitch == 1) {
        SDL_RenderCopy(renderer, wintext, NULL, &winrect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
    }
    if (wlswitch == 2) {
        SDL_RenderCopy(renderer, losetext, NULL, &loserect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
    }
    if (playables[playerNum].checkCollide(&door)) {
        wlswitch = 1;
        youWin = true;
        gameOver = true;
    }
    if (playables[playerNum].getReallyRectY() > height - 25) {
        GameScreen::reset();
    }
}

void GameScreen::reset(){
  //We will need the level object to replace dead enemies
  //delete enemies;
  level.read(levelfile);
  //cout << "loaded reset" << endl;
  if(lives > 0){
    //Move player back to start
   SDL_Rect playerLoc = *playables[playerNum].getTrueRect();
   for(int x = 0; x < (int) playables.size(); x++){
      playables[x].move(level.playerInitX-playerLoc.x, level.playerInitY-playerLoc.y);
    }

    //Reset all enemies
   //delete enemies;
    enemies = level.enemies;
    ground = level.ground;
    //pit = level.pit;
    door = level.door;
    level.door.prepFree();
    //gameOver = false;
    //cout << "enemies reset" << endl;
    lives--;
  } else {
    //You are out of lives: game over
    wlswitch = 2;
    gameOver = true;
  }
}

void GameScreen::hardReset() {
    levelnum = 1;
    levelfile = "level" + to_string(levelnum) + ".txt";
    //level = LevelEditor(levelfile);
    level.read(levelfile);
    SDL_Rect playerLoc = *playables[playerNum].getTrueRect();
    for (int x = 0; x < (int)playables.size(); x++) {
        playables[x].move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
    }
    //delete enemies;
    enemies = level.enemies;
    ground = level.ground;
    pit = level.pit;
    door = level.door;
    level.door.prepFree();
    width = level.levelWidth;
    height = level.levelHeight;
    camera.updateBounds(width, height);
    lives = 5;
    score = 0;
    gameOver = false;
    wlswitch = 0;
}

void GameScreen::advanceLevel() {
    levelnum++;
    levelfile = "level" + to_string(levelnum) + ".txt";
    level.read(levelfile);
    SDL_Rect playerLoc = *playables[playerNum].getTrueRect();
    for (int i = 0; i < (int)playables.size(); i++) {
        playables[i].move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
    }
    enemies = level.enemies;
    ground = level.ground;
    pit = level.pit;
    door = level.door;
    level.door.prepFree();
    width = level.levelWidth;
    height = level.levelHeight;
    camera.updateBounds(width, height);
    gameOver = false;
    wlswitch = 0;
    youWin = false;
}
