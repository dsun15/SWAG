/*
* S.W.A.G.
* Chris, Devin, Kevin, William
* 600.255 Intro to Video Game Design
*
*/

#include "GameScreen.h"
#include "AutoMovable.h"
#include "Movable.h"
#include "Screen.h"
#include "Camera.h"
#include "LevelEditor.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <list>

int width = 1000;
int height = 600;
SDL_Texture* gTexture;
SDL_Texture* gTexture2;
Movable door;
Movable player;
AutoMovable enemy[4];
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
SDL_Rect winrect = { 400, 50, 300, 50 };
SDL_Rect loserect = { 400, 50, 300, 50 };
SDL_Rect continuerect = { 100, 125, 600, 50 };
SDL_Rect gamescorerect = { 50, 50, 75, 50 };
int wlswitch; // 1 = win, 2 = lose
int score;
TTF_Font* gamefont;
bool scorewritten = false;
Camera camera;
Movable g1 =Movable("Texture1.png",300,300,0,300,3800,600,300,300,false,false);
Movable g2 =Movable("Texture2.png",75,200,300,400,3800,600,75,200,false,false);
Movable g3 =Movable("Texture3.png",75,100,375,500,3800,600,75,100,false,false);
Movable g4 =Movable("Texture4.png",300,25,500,300,3800,600,300,25,false,false);
Movable g5 =Movable("Texture4.png",300,25,1000,300,3800,600,300,25,false,false);
Movable g6 =Movable("Texture6.png",400,300,1500,300,3800,600,400,300,false,false);
Movable g7 =Movable("Texture7.png",400,100,1900,500,3800,600,400,100,false,false);
Movable g8 =Movable("Texture8.png",150,200,2300,400,3800,600,150,200,false,false);
Movable g9 =Movable("Texture9.png",350,300,2450,300,3800,600,350,300,false,false);
Movable g10 =Movable("Texture10.png",700,100,2800,500,3800,600,700,100,false,false);
Movable g11 =Movable("Texture11.png",300,200,3500,400,3800,600,300,200,false,false);

LevelEditor level = LevelEditor("level1.txt");
/*std::list<Movable> ground;
std::list<Movable> enemies;
std::list<Movable> pit;*/
Movable * ground[11];
//Movable enemies[level.enemies.size()];
//Movable pit[level.pit.size()];

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer* renderer) {
    //Level Stuff
    level = LevelEditor("level1.txt");
    width = level.levelWidth;
    height = level.levelHeight;
    
    //Player, Camera
    camera = Camera(level.levelWidth, level.levelHeight, 0, 0, 800, 600);
    player = Movable("player1.png", 50, 50, 0, 0, width, height, 600, 50);
    player.accelerate(1, 0);

    //Objects from level file
    /* ground = level.ground;
    enemies = level.enemies;
    pit = level.pit;*/
    int count = 0;
    /*while (level.ground.size() != 0) {
      ground[count] = &(level.ground.front());
      level.ground.pop_front();
      count++;
      }*/
    for (std::list<Movable>::iterator it = level.ground.begin(); it != level.ground.end(); ++it) {    
      /*Movable m;
	m = *it;*/
      ground[count] = &(*it);
      //std::cout << ground[count]->getReallyRectX() << " " << ground[count]->getReallyRectY()<<std::endl;
      count++;
    }
    count = 0;
    /*while (level.enemies.size() != 0) {
      enemies[count] = level.enemies.pop_front();
      count++;
	}
    count = 0;
    while (level.pit.size() != 0) {
      pit[count] = level.pit.pop_front();
      count++;
      }*/


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
    wlswitch = 0;
    score = 0;
    scorewritten = false;

    /*for (int i = 0; i <11; i++) {
      std::cout << ground[i] << std::endl;
      std::cout << ground[i]->getReallyRectX() << " " << ground[i]->getReallyRectY()<<std::endl;
      }*/
    return;
}

GameScreen::~GameScreen() {
    // Mix_FreeMusic(music);
    if (Mix_PlayingMusic())
        Mix_PauseMusic();
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
  SDL_Rect playerLoc = *player.getRect();
  SDL_Rect cameraLoc = *camera.getRect();
  //this works
  camera.center(player.getReallyRectX() + (playerLoc.w / 2), player.getReallyRectX() + (playerLoc.h / 2));

  if(door.checkCollide(camera.getRect())){
    door.draw(renderer, dt, -cameraLoc.x, 0, true);
  }
  //ground.front().draw(renderer, dt, -cameraLoc.x,0);
    /*for (std::list<Movable>::iterator it = ground.begin(); it != ground.end(); ++it) {
      Movable temp = *it;
        temp.draw(renderer, dt, -cameraLoc.x, 0);
        std::cout << temp.getTrueRect()->x << " " << (*it).getTrueRect()->y << std::endl;
    }
   
     for (std::list<Movable>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
        SDL_Rect* temp = player.getRect();
        SDL_Rect* enemyTemp = (*it).getRect();
        if (player.checkCollide(enemyTemp)) {
            gameOver = true;
            if ((temp->y < enemyTemp->y) && (abs(temp->x - enemyTemp->x) <= enemyTemp->w)) {
                enemies.erase(it);
                gameOver = false;
            }
        } else { 
            (*it).draw(renderer, dt, -cameraLoc.x, 0);
        }
    }
    
    for (std::list<Movable>::iterator it = pit.begin(); it != pit.end(); ++it) {
        (*it).draw(renderer, dt, -cameraLoc.x, 0);
	}*/
    /*ground[0] = &g1;
    ground[1] = &g2;
    ground[2] =&g3;
    ground[3] =&g4;
    ground[4] =&g5;
    ground[5] =&g6;
    ground[6] =&g7;
    ground[7] =&g8;
    ground[8] =&g9;
    ground[9] =&g10;
    ground[10] =&g11;*/

  bool playerOnGround = false;

    for (int i = 0; i < 11; i++) {

      
      if (ground[i]->checkCollide(&cameraLoc)) {
	ground[i]->draw(renderer, dt, -cameraLoc.x, 0, true);
	}
      if (player.checkCollide(ground[i])) {
	if (playerLoc.y <= ground[i]->getRect()->y && !player.getAir()) {
	  player.setVelY(0);
	  player.setGravity(0);
	  playerOnGround = true;
	  player.move(0, ground[i]->getRect()->y - playerLoc.y - playerLoc.h -1 );
	}
	else if(playerLoc.x < ground[i]->getRect()->x) {
	  player.setVelX(0);
	  player.move(ground[i]->getRect()->x - playerLoc.x - playerLoc.w, 0);
	}
	else if(playerLoc.x > ground[i]->getRect()->x){

	  player.setVelX(0);
	  player.move((ground[i]->getRect()->x + ground[i]->getRect()->w) - playerLoc.x, 0);

	}
      }
    }
    

    player.draw(renderer, dt, -cameraLoc.x, 0, playerOnGround);
    
    string temp = std::to_string(score);
    const char* temp2 = temp.c_str();
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* ss = TTF_RenderUTF8_Blended(gamefont, temp2, white);
    scoretext = SDL_CreateTextureFromSurface(renderer, ss);
    SDL_RenderCopy(renderer, scoretext, NULL, &gamescorerect);
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
   /* for (int i = 0; i < 4; i++) {
        // check collisions
        if (player.checkCollide(&(enemy[i])) && onScreen[i]) {
            Mix_PlayChannel(-1, sfx, 1);
            // jump on enemy for a kill
            SDL_Rect* temp = player.getRect();
            SDL_Rect* enemyTemp = enemy[i].getRect();
            if ((temp->y < enemyTemp->y) && (abs(temp->x - enemyTemp->x) <= enemyTemp->w)) {
                onScreen[i] = false;
                score = score + 100;
                // you die
            } else {
                wlswitch = 2;
                gameOver = true;
            }
        }

        // render enemeies
        if (onScreen[i] && enemy[i].checkCollide(camera.getRect())) {
	  enemy[i].automove(dt);
	  enemy[i].draw(renderer, dt, -cameraLoc.x, 0);
        }
    }*/
}
