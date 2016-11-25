/*                                                                                                                              
 * S.W.A.G.                                                                                                                      
 * Chris, Devin, Kevin, William                                                                                                  
 * 600.255 Intro to Video Game Design                                                                                            
 *                                                                                                                               
 */

#include "Helper.h"
#include "Movable.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
using std::string;

Helper::Helper() {}
Helper::~Helper() {}

int Helper::getInitX() {
  return this->initX;
}

int Helper::getInitY() {
  return this->initY;
}
