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
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>

int width = 1000;
int height = 600;
SDL_Texture* gTexture;
SDL_Texture* gTexture2;
Movable door;
Movable player;
AutoMovable enemy[4];
bool gameOver = false;
bool youWin = false;
bool onScreen[] = { true, true, true, true };
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

GameScreen::GameScreen() {}
GameScreen::GameScreen(SDL_Renderer* renderer) {
  camera = Camera(1000, 600, 0, 0, 800, 600);
    player = Movable("player1.png", 50, 50, 0, 0, width, height, 600, 50);
    player.accelerate(1, 0);
    Mix_HaltChannel(1);
    Mix_Resume(1);
    for (int i = 0; i <= 3; i++) {
      //enemy[i] = AutoMovable("enemy1.png", 50, 50, (200 + 100 * i), (550), width,height, 300, 50);
    }
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
    for (int i = 0; i < 4; i++) {
        onScreen[i] = true;
    }
    door = Movable("door.png", 50, 50, 950, 550, width, height, 50, 50, false);
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
        //                inFile.close();
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
            if (event->key.keysym.sym == SDLK_SPACE) {
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
  camera.center(playerLoc.x + (playerLoc.w / 2), playerLoc.y + (playerLoc.h / 2));
  std::cout << cameraLoc.x << cameraLoc.y << "\n";
  player.draw(renderer, dt, -cameraLoc.x, 0);
  if(door.checkCollide(camera.getRect())){
    door.draw(renderer, dt, -cameraLoc.x, 0);
  }
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
    for (int i = 0; i < 4; i++) {
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
    }
}
