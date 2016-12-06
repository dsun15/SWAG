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
#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unistd.h>
#include <vector>
using namespace std;
SDL_Renderer * renderer;
int width = 1000;
int height = 600;
Movable door;
const int MAX_LV = 5;
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
const char* cont = "[Press Enter To Continue]";
SDL_Texture* wintext;
SDL_Texture* losetext;
SDL_Texture* continuetext;
SDL_Texture* scoretext;
SDL_Texture* lifetext;
SDL_Texture* background[MAX_LV];
SDL_Texture* spriteLives;
SDL_Rect winrect = { 400, 50, 300, 50 };
SDL_Rect loserect = { 400, 50, 300, 50 };
SDL_Rect continuerect = { 395, 50, 400, 50 };
SDL_Rect gamescorerect = { 50, 50, 45, 50 };
SDL_Rect lifecountrect = { 725, 525, 45, 50 };
SDL_Rect backrect = { 0, 0, 800, 600 };
SDL_Rect livesRect = { 665, 533, 40, 40 };
int wlswitch; // 1 = win, 2 = lose
int score;
TTF_Font* gamefont;
bool scorewritten = false;
Camera camera;
int lives;
int playerNum = 0;

Movable* jibby;
Movable* arrow;

int levelnum = 0;
string levelfile;
LevelEditor level; // = LevelEditor(levelfile);
std::vector<Movable*> playables;
std::list<AutoMovable>* ground;
std::vector<AutoMovable>* enemies;
std::list<AutoMovable>* pit;

std::list<Movable*>* text;
vector<SDL_Texture*>* textVector;

vector<SDL_Surface*> surfaceVector;
SDL_Surface* bs[MAX_LV]; /* = IMG_Load("BackgroundGradient1.png");*/
SDL_Surface* jibbyIcon = IMG_Load("jibbyOneFrame.png");

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer* render) {
    //set starting lives
    lives = 5;
    renderer = render;
    //Level Stuff
    levelfile = "level" + to_string(levelnum) + ".txt";
    level.read(levelfile);
    width = level.levelWidth;
    height = level.levelHeight;
    for (int i = 0; i < MAX_LV; i++) {
        string backfile = "BackgroundGradient" + to_string(i) + ".png";
        bs[i] = IMG_Load(backfile.c_str());
        background[i] = SDL_CreateTextureFromSurface(renderer, bs[i]);
    }
    spriteLives = SDL_CreateTextureFromSurface(renderer, jibbyIcon);

    //Player, Camera
    camera = Camera(level.levelWidth, level.levelHeight, 0, 0, 800, 600);

    jibby = new Movable("jibbyidle.png", 50, 50, 0, 0, width, height, 950, 50);
    arrow = new Movable("arrow.png", 30, 30, 0,0,width, height, 300, 30, false, true);
    
    //Movable * brad = new Movable("player1.png", 50, 50, 100, 0, width, height, 600, 50);
    //cout << "placing" << endl;
    playables.push_back(jibby);
    //cout << "placed one" << endl;
    //playables.push_back(brad);
    //cout << "placed two" << endl;
    //jibby->prepFree();
    //jibby2->prepFree();

    //Objects from level file
    ground = level.ground;
    enemies = level.enemies;
    pit = level.pit;
    text = level.text;

    door = level.door;
    level.door.prepFree();
    for (list<Movable*>::iterator it = level.helpers->begin(); it != level.helpers->end(); ++it) {
        playables.push_back(*it);
    }
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
    gamefont = TTF_OpenFont("8bit.ttf", 65);
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
    //SDL_Surface* tempSurf;

    //initializing text
    textVector = new vector<SDL_Texture*>;
    for (list<Movable*>::iterator it = text->begin(); it != text->end(); ++it) {
        string temp = (*it)->getName();
        temp = temp.substr(0, temp.size() - 1);
        textVector->push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderUTF8_Blended(gamefont, temp.c_str(), white)));
    }

    scorewritten = false;
    return;
}

GameScreen::~GameScreen() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(sfx);
    Mix_FreeChunk(sfxJump);
    SDL_DestroyTexture(wintext);
    SDL_DestroyTexture(losetext);
    SDL_DestroyTexture(continuetext);
    SDL_DestroyTexture(scoretext);
    SDL_DestroyTexture(lifetext);
    SDL_DestroyTexture(spriteLives);
    SDL_FreeSurface(jibbyIcon);
    TTF_CloseFont(gamefont);
    for (int i = 0; i < MAX_LV; i++) {
        SDL_FreeSurface(bs[i]);
        SDL_DestroyTexture(background[i]);
    }
    delete jibby;
    delete arrow;
    for (vector<SDL_Texture *>::iterator it = textVector->begin(); it!=textVector->end(); ++it) {
        SDL_DestroyTexture(*it);
    }
    delete textVector;
    for (vector<SDL_Texture*>::iterator it = textVector->begin(); it != textVector->end(); ++it) {
        SDL_DestroyTexture(*it);
    }
}

int GameScreen::findDistances() {

    vector<double> distances;
    distances.push_back(10000);
    //playables index
    int closest = playerNum;
    for (int x = 0; x < (int)playables.size(); x++) {

        if (x != playerNum) {

            double temp = abs(playables[x]->getTrueRect()->x - playables[playerNum]->getTrueRect()->x /* + ((playables[x]->getTrueRect()->y - playables[playerNum]->getTrueRect()->y)^2)*/);
            if (temp < distances.back()) {
                distances.push_back(temp);
                closest = x;
            }
        }
    }

    return closest;
}

int GameScreen::input(SDL_Event* event, int dt) {

    if (gameOver) {
        playables[playerNum]->setVelX(0);
        std::ofstream inFile;
        inFile.open("scores.txt", std::ios_base::app);
        if (!scorewritten) {
            inFile << score << "\n";
            scorewritten = true;
        }
        if (event->key.keysym.sym == SDLK_RETURN) {
            if (levelnum == MAX_LV) {
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
                playables[playerNum]->setMove(false);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                playables[playerNum]->setMove(false);
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
            if (event->key.keysym.sym == SDLK_w) {

                //only works if jibby is 0
                playerNum = 0;
            }
            if (event->key.keysym.sym == SDLK_e) {
                playables[playerNum]->setVelX(0);
                if (playerNum + 1 >= (int)playables.size()) {
                    playerNum = 0;
                } else {
                    playerNum++;
                }
            }
            if (event->key.keysym.sym == SDLK_q) {

                playables[playerNum]->setVelX(0);
                playerNum = GameScreen::findDistances();
                /*if (playerNum - 1 < 0) {
		  playerNum = (int)playables.size() - 1;
                } else {
                    playerNum--;
		}*/
            }
            break;

        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_RIGHT) {
                option = 3;
                playables[playerNum]->accelerate(dt, 1, 0);
                playables[playerNum]->setMove(true);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                option = 4;
                playables[playerNum]->accelerate(dt, -1, 0);
                playables[playerNum]->setMove(true);
            }
            if (event->key.keysym.sym == SDLK_DOWN) {
                option = 1;
            }
            if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP) {
                Mix_PlayChannel(-1, sfxJump, 0);
                option = 2;
                if (!playables[playerNum]->getAir()) {
                    playables[playerNum]->accelerate(15, 0, -3);
                    //playables[playerNum].jump();
                }
            }
            break;
        }
    }
    return 0;
}

void GameScreen::draw(SDL_Renderer* renderer, int dt) {
    //cout << "draw" << endl;
    SDL_RenderCopy(renderer, background[levelnum], NULL, &backrect);

    SDL_Rect cameraLoc = *camera.getRect();
    bool playerOnGround = false;

    //camera centering
    camera.center(playables[playerNum]->getReallyRectX() + (playables[playerNum]->getRect()->w / 2), playables[playerNum]->getReallyRectY() + (playables[playerNum]->getRect()->h / 2));
    if (door.checkCollide(camera.getRect())) {
        door.draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
    }

    //printing text
    vector<SDL_Texture*>::iterator iterator = textVector->begin();
    for (std::list<Movable*>::iterator it = text->begin(); it != text->end(); ++it) {
        // if ((*it).checkCollide(&cameraLoc)) {
        SDL_Rect temp = { (*it)->getTrueRect()->x - cameraLoc.x, (*it)->getTrueRect()->y - cameraLoc.y, (*it)->getTrueRect()->w, (*it)->getTrueRect()->h };
        //SDL_RenderCopy(renderer, *iterator, NULL, ((*it)->getTrueRect()));
        SDL_RenderCopy(renderer, *iterator, NULL, &temp);
        // }

        ++iterator;
    }

    for (int z = 0; z < (int)playables.size(); z++) {

        SDL_Rect* playrect = playables[z]->getTrueRect();
        playables[z]->setStacked(-1);
        bool anyCollide = false;
        bool playerCollide = false;

        //player-player collision
        for (int x = 0; x < (int)playables.size(); x++) {
            if (playables[x]->checkCollide(playrect)) {
                SDL_Rect* xrect = playables[x]->getTrueRect();
                if (xrect->y + .8 * xrect->h < playrect->y && xrect->x + 0.8 * xrect->w > playrect->x && xrect->x + 0.2 * xrect->w < playrect->x + playrect->w) {
                    // from above
                    playerOnGround = true;
                    playables[x]->setLowerBound(playrect->y + 1);

                    playerCollide = true;
                } else if (xrect->y > playrect->y + .8 * playrect->h && xrect->x + .8 * xrect->w > playrect->x && xrect->x + .2 * xrect->w < playrect->x + playrect->w) {
                    //There is someone on top, get ready to bring them with
                    // from below
                    playables[x]->setUpperBound(playrect->y + playrect->h);
                    playerOnGround = false;
                    playables[z]->setStacked(x);
                    playerCollide = true;
                } else if (xrect->x < playrect->x && xrect->y >= playrect->y) {
                    // from left
                    playables[x]->setRightBound(playrect->x + 1);
                    playerCollide = true;
                } else if (xrect->x > playrect->x && xrect->y >= playrect->y) {

                    // from right
                    playables[x]->setLeftBound(playrect->x + playrect->w - 1);
                    playerCollide = true;
                }
            }
        }

        if (!anyCollide) {
            playables[z]->setUpperBound(0);
            playables[z]->setLeftBound(0);
            playables[z]->setRightBound(width);
            playables[z]->setLowerBound(height + 100);
        }

        //ground collisions
        for (std::list<AutoMovable>::iterator it = ground->begin(); it != ground->end(); ++it) {
            if ((*it).getAnimate()) {
                (*it).hoverBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
            }
            if ((*it).checkCollide(&cameraLoc)) {
                (*it).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
            }
            if (playables[z]->checkCollide(&*it)) {
                SDL_Rect* itrect = (*it).getTrueRect();
                anyCollide = true;
                if (playrect->y + .8 * playrect->h < itrect->y && (playrect->x + 0.8 * playrect->w) > itrect->x && playrect->x + 0.2 * playrect->w < itrect->x + itrect->w) {
                    //above
                    playerOnGround = true;
                    //playables[z].move(0,-1);
                    playables[z]->setLowerBound(itrect->y + 1);

                } else if (playrect->y > itrect->y && playrect->x > itrect->x && playrect->x + playrect->w < itrect->x + itrect->w) {
                    //below
                    playables[z]->setUpperBound(itrect->y + itrect->h);
                } else if (playrect->x < itrect->x && playrect->y + playrect->h != itrect->y + 1) {

                    // from left
                    playables[z]->setRightBound(itrect->x + 1);
                } else if (playrect->x > itrect->x && playrect->y + playrect->h != itrect->y + 1) {
                    //from right
                    playables[z]->setLeftBound(itrect->x + itrect->w - 1);
                }
            }
        }
    }

    //collision with enemies
    vector<AutoMovable>::iterator iter = enemies->begin();
    while (iter != enemies->end()) {
        if (!((*iter).getGravity())) {
            (*iter).moveBetween((*iter).getMinMoveBound(), (*iter).getMaxMoveBound(), dt);
        }
        if ((*iter).getLife() /*(*iter).checkCollide(&cameraLoc)*/) {
            (*iter).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
        }
        if (playables[playerNum]->checkCollide((*iter).getTrueRect()) && (*iter).getLife()) {
            if (playables[playerNum]->getTrueRect()->y < (*iter).getTrueRect()->y) {
                //enemy kill;
                playables[playerNum]->setVelY(-4);
                score += 100;
                (*iter).setLife(false);
            } else {
                Mix_PlayChannel(-1, sfx, 0);
                iter = enemies->end();
                if (!gameOver) {
                    GameScreen::reset();
                }
            }
        } else {
            ++iter;
        }
    }

    //non-killable enemies
    for (std::list<AutoMovable>::iterator it = pit->begin(), end = pit->end(); it != end; ++it) {
        //if no gravity, then it is moving between a bounds
        if (!((*it).getGravity())) {
            (*it).moveBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
        }
        (*it).draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
        if (playables[playerNum]->checkCollide((*it).getTrueRect())) {
            Mix_PlayChannel(-1, sfx, 0);
            if (!gameOver) {
                GameScreen::reset();
            }
            it = end;
        }
    }

    for (int z = 0; z < (int)playables.size(); z++) {

        if (playables[z]->checkCollide(&cameraLoc)) {
            if (z == playerNum) {
                playables[z]->draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, playerOnGround);
            } else {
                if (playables[z]->getStacked() == playerNum) {
		  playables[z]->move(playables[playerNum]->getTrueRect()->x + (playables[playerNum]->getTrueRect()->w / 2) - playables[z]->getTrueRect()->x - (playables[z]->getTrueRect()->w / 2),
				     playables[playerNum]->getTrueRect()->y + (playables[playerNum]->getTrueRect()->h / 2) - playables[z]->getTrueRect()->y - (playables[z]->getTrueRect()->h / 2));
                    playables[z]->draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);

                } else {

                    playables[z]->draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
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
    SDL_DestroyTexture(scoretext);
    SDL_DestroyTexture(lifetext);
    if (wlswitch == 1) {
        //     SDL_RenderCopy(renderer, wintext, NULL, &winrect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
    }
    if (wlswitch == 2) {
        //        SDL_RenderCopy(renderer, losetext, NULL, &loserect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
    }
    if (playables[0]->checkCollide(&door)) {
        wlswitch = 1;
        youWin = true;
        gameOver = true;
    }
    if (playables[playerNum]->getReallyRectY() > height - 25) {
        GameScreen::reset();
    }
    SDL_Rect* playerLoc = playables[playerNum]->getTrueRect();
    SDL_Rect* arrowLoc = arrow->getTrueRect();
    arrow->move(playerLoc->x - arrowLoc->x + playerLoc->w/2-arrowLoc->w/2, playerLoc->y - arrowLoc->y - 50);
    arrow->draw(renderer, dt, -cameraLoc.x, -cameraLoc.y, true);
    //camera.center(playables[playerNum]->getReallyRectX() + (playables[playerNum]->getRect()->w / 2), playables[playerNum]->getReallyRectY() + (playables[playerNum]->getRect()->h / 2));
}

void GameScreen::reset() {
    //We will need the level object to replace dead enemies
    //delete enemies;
    level.read(levelfile);
    if (lives > 0) {
        //Move player back to start
        SDL_Rect playerLoc = *playables[0]->getTrueRect();
        playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
        playables.clear();
        playables.push_back(jibby);
        for (list<Movable*>::iterator it = level.helpers->begin(); it != level.helpers->end(); ++it) {
            playables.push_back(*it);
        }
        /*for (int x = 0; x < (int)playables.size(); x++) {
          if (x==0) {
	    //this should always be jibby
	    playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
	  } else { //the rest should be helpers
	    SDL_Rect helperLoc = *playables[x]->getTrueRect();
	    playables[x]->move(playables[x]->getInitX() - helperLoc.x, playables[x]->getInitY() - helperLoc.y);
	  }
	  }*/
        //camera.move(playerLoc.x - camera.getTrueRect()->x, playerLoc.y - camera.getTrueRect()->y);
        camera.move(level.playerInitX - camera.getTrueRect()->x, level.playerInitY - camera.getTrueRect()->y);
        //Reset all enemies
        //delete enemies;
        enemies = level.enemies;
        ground = level.ground;
        //pit = level.pit;
        door = level.door;
        level.door.prepFree();
        //gameOver = false;
        if (playerNum == 0) {
            lives--;
        }
    } else {
        //You are out of lives: game over
        wlswitch = 2;
        gameOver = true;
    }
}

void GameScreen::hardReset() {
    levelnum = 0;
    levelfile = "level" + to_string(levelnum) + ".txt";
    //level = LevelEditor(levelfile);
    level.read(levelfile);
    SDL_Rect playerLoc = *playables[0]->getTrueRect();
    playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
    playables.clear();
    playables.push_back(jibby);
    for (list<Movable*>::iterator it = level.helpers->begin(); it != level.helpers->end(); ++it) {
        playables.push_back(*it);
    }
    /*for (int x = 0; x < (int)playables.size(); x++) {
        playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
	}*/
    //delete enemies;
    enemies = level.enemies;
    ground = level.ground;
    pit = level.pit;
    door = level.door;
    /*for (vector<SDL_Texture *>::iterator it = textVector->begin(); it!=textVector->end(); ++it) {
      SDL_DestroyTexture(*it);
    }
    textVector.clear();*/
    text = level.text;
    GameScreen::textPrep();

    level.door.prepFree();
    width = level.levelWidth;
    height = level.levelHeight;
    camera.updateBounds(width, height);
    camera.move(-1 * camera.getTrueRect()->x, -1 * camera.getTrueRect()->y);
    lives = 5;
    score = 0;
    gameOver = false;
    wlswitch = 0;
    playerNum = 0;
    arrow->setRightBound(width);
    arrow->setLowerBound(height);
}

void GameScreen::advanceLevel() {
    levelnum++;
    levelfile = "level" + to_string(levelnum) + ".txt";
    level.read(levelfile);
    SDL_Rect playerLoc = *playables[playerNum]->getTrueRect();
    playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
    playables.clear();
    playables.push_back(jibby);
    for (list<Movable*>::iterator it = level.helpers->begin(); it != level.helpers->end(); ++it) {
        playables.push_back(*it);
    }
    /*for (int i = 0; i < (int)playables.size(); i++) {
        playables[0]->move(level.playerInitX - playerLoc.x, level.playerInitY - playerLoc.y);
	}*/
    enemies = level.enemies;
    ground = level.ground;
    pit = level.pit;
    door = level.door;
    text = level.text;
    GameScreen::textPrep();
    level.door.prepFree();
    playerNum = 0;
    width = level.levelWidth;
    height = level.levelHeight;
    camera.updateBounds(width, height);
    camera.move(level.playerInitX - camera.getTrueRect()->x, level.playerInitY - camera.getTrueRect()->y);
    gameOver = false;
    wlswitch = 0;
    youWin = false;
    arrow->setRightBound(width);
    arrow->setLowerBound(height);
}

void GameScreen::textPrep() {
  //assumes already text = level.text
  for (vector<SDL_Texture *>::iterator it = textVector->begin(); it!=textVector->end(); ++it) {
    SDL_DestroyTexture(*it);
  }
  textVector->clear();
  SDL_Color white = { 255, 255, 255, 255 };
  for (list<Movable*>::iterator it = text->begin(); it != text->end(); ++it) {
    string temp = (*it)->getName();
    temp = temp.substr(0, temp.size() - 1);
    textVector->push_back(SDL_CreateTextureFromSurface(renderer, TTF_RenderUTF8_Blended(gamefont, temp.c_str(), white)));
  }
}
