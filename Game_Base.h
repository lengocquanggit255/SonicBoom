#ifndef GAME_BASE_
#define GAME_BASE_

#include "src/include/SDL.h"
#include "src/include/SDL_image.h"
#include "src/include/SDL_mixer.h"
#include "src/include/SDL_ttf.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TTF_ERROR 4

#define MIX_CHANNEL -1

#define TIME_MAX 1000
#define GROUND 430
#define MAX_HEIGHT 250

#define BASE_OFFSET_SPEED 0

#define SPEED_INCREASEMENT 1
#define SCORE_INCREASEMENT 1
#define TIME_INCREASEMENT 1
#define FRAME_INCREASEMENT 1

#define GROUND_SPEED 5
#define ENEMY_SPEED 5
#define MAX_ENEMY_WIDTH 100

#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define SLOW_FRAME_CHAR 6// 24 frame
#define SLOW_FRAME_ENEMY 6

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2
#define BACK_BUTTON 3
#define CHOOSE_CHARACTER_BUTTON 4

const std::string WINDOW_TITLE = "Sonic Boom";

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;
const int BACK_BUTTON_WIDTH = 100;
const int BACK_BUTTON_HEIGHT = 78;
const int CHOOSE_CHARACTER_BUTTON_WIDTH = 260;
const int CHOOSE_CHARACTER_BUTTON_HEIGHT = 350;

const int PLAY_BUTON_POSX = 389;
const int PLAY_BUTTON_POSY= 186;
const int HELP_BUTTON_POSX = 389;
const int HELP_BUTTON_POSY = 293;
const int EXIT_BUTTON_POSX = 389;
const int EXIT_BUTTON_POSY = 402;
const int BACK_BUTTON_POSX = 31;
const int BACK_BUTTON_POSY = 29;
const int PAUSE_BUTTON_POSX = 31;
const int PAUSE_BUTTON_POSY = 29;
const int CONTINUE_BUTTON_POSX = 31;
const int CONTINUE_BUTTON_POSY = 29;
const int CHOOSE_SONIC_BUTTON_POSX = 36;
const int CHOOSE_SONIC_BUTTON_POSY = 80;
const int CHOOSE_SHADOW_BUTTON_POSX = 630;
const int CHOOSE_SHADOW_BUTTON_POSY = 80;


const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int SCORE_POSX = 830;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 830;
const int HIGH_SCORE_POSY = 80;

const double LAYER_SPEED = 1.5;
const int RUNNING_FRAMES = 4;
const int FLYING_ENEMY_FRAMES = 4;
const int GROUND_ENEMY_FRAMES = 4;


void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_