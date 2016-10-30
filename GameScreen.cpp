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
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unistd.h>
using namespace std;
int width = 1000;
int height = 600;
SDL_Texture* gTexture;
SDL_Texture* gTexture2;
Movable door;
Movable player;
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
SDL_Texture* background;
SDL_Rect winrect = { 400, 50, 300, 50 };
SDL_Rect loserect = { 400, 50, 300, 50 };
SDL_Rect continuerect = { 100, 125, 600, 50 };
SDL_Rect gamescorerect = { 50, 50, 75, 50 };
SDL_Rect lifecountrect = { 725, 525, 75, 50 };
SDL_Rect backrect = {0,0,800,600};
int wlswitch; // 1 = win, 2 = lose
int score;
TTF_Font* gamefont;
bool scorewritten = false;
Camera camera;
int lives;

string levelfile = "level2A.txt";
LevelEditor level = LevelEditor(levelfile);
std::list<Movable> ground;
std::list<AutoMovable> enemies;
std::list<AutoMovable> pit;

SDL_Surface* bs = IMG_Load("BackgroundGradient.png");

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer* renderer) {
    std::cout << "YO" << std::endl;
  //set starting lives
  lives = 5;
  
    //Level Stuff
    //level = LevelEditor("level1.txt");
  //level = LevelEditor("level2A.txt");
  level = LevelEditor(levelfile);
    width = level.levelWidth;
    height = level.levelHeight;
//    SDL_Surface* bs = IMG_Load("BackgroundGradient.png");
    background = SDL_CreateTextureFromSurface(renderer, bs);
//    SDL_FreeSurface(bs);
    //Player, Camera
    camera = Camera(level.levelWidth, level.levelHeight, 0, 0, 800, 600);
    //player = Movable("player1.png", 50, 50, 0, 0, width, height, 600, 50);
    //player = Movable("jibbyidle.png", 50, 50, 0, 0, width, height, 800, 50);
    player = Movable("jibbyidle.png", 50, 50, level.playerInitX, level.playerInitY, width, height, 800, 50);
    player.accelerate(1, 0);

    //Objects from level file
    ground = level.ground;
    enemies = level.enemies;
    pit = level.pit;

    //test enemy
  //  enemy = AutoMovable("enemy1.png", 50, 50, 2000, 450, width, height, 300, 50, false, true);

    door = level.door;

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
    TTF_Init();
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
    //std::cout << "destruct" << std::endl;
    Mix_FreeMusic(music);
    Mix_FreeChunk(sfx);
    Mix_FreeChunk(sfxJump);
    SDL_DestroyTexture(wintext);
    SDL_DestroyTexture(losetext);
    SDL_DestroyTexture(continuetext);
    SDL_DestroyTexture(scoretext);
    SDL_DestroyTexture(lifetext);
    SDL_DestroyTexture(background);
    SDL_FreeSurface(bs);
}

int GameScreen::input(SDL_Event* event, int dt) {
    if (gameOver) {
        player.setVelX(0);
        std::ofstream inFile;
        inFile.open("scores.txt", std::ios_base::app);
        if (!scorewritten) {
            inFile << score << "\n";
            scorewritten = true;
        }
        if (event->key.keysym.sym == SDLK_RETURN) {
            return 3;
        }

    } else {
        switch (event->type) {
        case SDL_KEYUP:
            if (event->key.keysym.sym == SDLK_RIGHT) {
                player.setMove(false);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                player.setMove(false);
            }
            if (event->key.keysym.sym == SDLK_DOWN) {
            }
            if (event->key.keysym.sym == SDLK_UP) {
            }
            break;

        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_RIGHT) {
                option = 3;
                player.accelerate(dt, 2);
                player.setMove(true);
            }
            if (event->key.keysym.sym == SDLK_LEFT) {
                option = 4;
                player.accelerate(dt, -2);
                player.setMove(true);
            }
            if (event->key.keysym.sym == SDLK_DOWN) {
                option = 1;
            }
            if (event->key.keysym.sym == SDLK_SPACE || event->key.keysym.sym == SDLK_UP) {
                Mix_PlayChannel(-1, sfxJump, 1);
                option = 2;
                player.jump();
            }
            break;
        }
    }
    return 0;
}

void GameScreen::draw(SDL_Renderer* renderer, int dt) {
  SDL_RenderCopy(renderer,background,NULL,&backrect);
    SDL_Rect playerLoc = *player.getTrueRect();
    SDL_Rect cameraLoc = *camera.getRect();
    //this works
    camera.center(player.getReallyRectX(), 0);

    if (door.checkCollide(camera.getRect())) {
        door.draw(renderer, dt, -cameraLoc.x, 0, true);
    }

    bool playerOnGround = false;
    bool anyCollide = false;
    //collision with platforms
    for (std::list<Movable>::iterator it = ground.begin(); it != ground.end(); ++it) {
        Movable temp = *it;
        if (temp.checkCollide(&cameraLoc)) {
            temp.draw(renderer, dt, -cameraLoc.x, 0, true);
        }
        if (player.checkCollide(&temp)) {
            if (playerLoc.y < temp.getTrueRect()->y) {
                //player.setVelY(0);
                //player.setGravity(0);
                playerOnGround = true;

                //player.move(0, temp.getTrueRect()->y - playerLoc.y - playerLoc.h - 1);
                player.setLowerBound(temp.getTrueRect()->y + 1);
            } else if (playerLoc.y >= temp.getTrueRect()->y && playerLoc.x < temp.getTrueRect()->x) {
                //player.setVelX(0);
                player.setRightBound(temp.getTrueRect()->x);
                //player.move(temp.getTrueRect()->x - playerLoc.x - playerLoc.w, 0);
            } else if (playerLoc.y >= temp.getTrueRect()->y && playerLoc.x > temp.getTrueRect()->x) {
                //player.setVelX(0);
                player.setLeftBound(temp.getTrueRect()->x + temp.getTrueRect()->w);
                //player.move((temp.getTrueRect()->x + temp.getTrueRect()->w) - playerLoc.x, 0);
            }
            anyCollide = true;
        }
    }
    if (!anyCollide) {
        player.setUpperBound(0);
        player.setLeftBound(0);
        player.setRightBound(width);
        player.setLowerBound(height + 100);
    }

    //collision with enemies
    //THIS DOESNT INCLUDE THE ONE ENEMY THATS HARDCODED IN
    for (std::list<AutoMovable>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        //if no gravity, then it is moving between a bounds
        if (!((*it).getGravity())) {
            //std::cout << temp.getMinMoveBound() << "     " << temp.getMaxMoveBound() << std::endl;
            (*it).moveBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
            //temp.setMove(true);
        }
        if ((*it).checkCollide(&cameraLoc)) {
            (*it).draw(renderer, dt, -cameraLoc.x, 0, true);

        }
        if (player.checkCollide(&*it)) {
            if (playerLoc.y < (*it).getTrueRect()->y) {
                //enemy kill;
                Mix_PlayChannel(-1, sfx, 1);
                player.setVelY(-4);
                enemies.erase(it);
                score += 100;
            } else {
	      GameScreen::reset();
            }
        }
    }
    //pits
    for (std::list<AutoMovable>::iterator it = pit.begin(); it != pit.end(); ++it) {
        //if no gravity, then it is moving between a bounds
        if (!((*it).getGravity())) {
            //std::cout << temp.getMinMoveBound() << "     " << temp.getMaxMoveBound() << std::endl;
            (*it).moveBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
            //temp.setMove(true);
        }
        if ((*it).checkCollide(&cameraLoc)) {
            (*it).draw(renderer, dt, -cameraLoc.x, 0, true);
            //if no gravity, then it is moving between a bounds
            if (!((*it).getGravity())) {
                (*it).moveBetween((*it).getMinMoveBound(), (*it).getMaxMoveBound(), dt);
            }
        }
        if (player.checkCollide(&*it)) {
	  /*wlswitch = 2;
            gameOver = true;
	  */
	  GameScreen::reset();
        }
    }
   // enemy.moveBetween(1900, 2300, dt);
   // enemy.draw(renderer, dt, -cameraLoc.x, 0, true);
    player.draw(renderer, dt, -cameraLoc.x, 0, playerOnGround);

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
    SDL_FreeSurface(ss);
    SDL_FreeSurface(ls);
    if (wlswitch == 1) {
        SDL_RenderCopy(renderer, wintext, NULL, &winrect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
        // usleep(2500000);
    }
    if (wlswitch == 2) {
        SDL_RenderCopy(renderer, losetext, NULL, &loserect);
        SDL_RenderCopy(renderer, continuetext, NULL, &continuerect);
        //    usleep(2500000);
    }
    if (player.checkCollide(&door)) {
        wlswitch = 1;
        youWin = true;
        gameOver = true;
    }
    if (playerLoc.y > height) {
      /*wlswitch = 2;
        gameOver = true;
      */
      GameScreen::reset();
    }
}

void GameScreen::reset(){
  //We will need the level object to replace dead enemies
  level = LevelEditor(levelfile);
  cout << "loaded reset" << endl;
  if(lives > 0){
    //Move player back to start
    SDL_Rect playerLoc = *player.getTrueRect();
    player.move(level.playerInitX-playerLoc.x, level.playerInitY-playerLoc.y);

    //Reset all enemies
    enemies = level.enemies;

    lives--;
  } else {
    //You are out of lives: game over
    wlswitch = 2;
    gameOver = true;
  }
}

void GameScreen::hardReset(){
    level = LevelEditor(levelfile);
    cout << "loaded hard reset" << endl;
    SDL_Rect playerLoc = *player.getTrueRect();
    player.move(level.playerInitX-playerLoc.x, level.playerInitY-playerLoc.y);
    enemies = level.enemies;
    lives = 5;
    score = 0;
    gameOver = false;
    wlswitch = 0;
}

