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
#include <cmath>

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
#define POWER_UP_SPEED 5
#define MAX_ENEMY_WIDTH 100
#define MAX_POWER_UP_WIDTH 100
#define IN_AIR_ENEMY 1
#define ON_GROUND_ENEMY 0

#define SLOW_FRAME_CHAR 6// 24 frame
#define SLOW_FRAME_ENEMY 6

#define IS_REPEATITIVE -1
#define NOT_REPEATITIVE 0

#define EASY_MODE 0
#define HARD_MODE 1

enum ButtonType{
    PLAY_BUTON,
    HELP_BUTTON,
    EXIT_BUTTON,
    OPTION_BUTTON,
    BACK_BUTTON,
    PAUSE_AND_CONTINUE_BUTTON,
    CHOOSE_CHARACTER_BUTTON,
    HARD_MODE_BUTTON,
    EASY_MODE_BUTTON,
    EXIT_OPTION_BUTTON
};

const std::string WINDOW_TITLE = "Sonic Boom";

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

const double PLAY_BUTON_WIDTH = 179;
const double PLAY_BUTON_HEIGHT = 49;
const double HELP_BUTTON_WIDTH = 171;
const double HELP_BUTTON_HEIGHT = 49;
const double EXIT_BUTTON_WIDTH = 157;
const double EXIT_BUTTON_HEIGHT = 49;
const double OPTION_BUTTON_WIDTH = 273;
const double OPTION_BUTTON_HEIGHT = 49;
const double HARD_MODE_BUTTON_WIDTH = 250;
const double HARD_MODE_BUTTON_HEIGHT = 75;
const double EASY_MODE_BUTTON_WIDTH = 250;
const double EASY_MODE_BUTTON_HEIGHT = 75;
const double EXIT_OPTION_BUTTON_WIDTH = 50;
const double EXIT_OPTION_BUTTON_HEIGHT = 50;
const double BACK_BUTTON_WIDTH = 146;
const double BACK_BUTTON_HEIGHT = 35;
const double PAUSE_AND_CONTINUE_BUTTON_WIDTH = 22;
const double PAUSE_AND_CONTINUE_BUTTON_HEIGHT = 34;
const double CHOOSE_CHARACTER_BUTTON_WIDTH = 280;
const double CHOOSE_CHARACTER_BUTTON_HEIGHT = 350;
const double CHARACTER_FRAME_WIDTH = 53;
const double CHARACTER_FRAME_HEIGHT = 57;
const double GROUND_ENEMY_FRAME_WIDTH = 29.25;
const double GROUND_ENEMY_FRAME_HEIGHT = 57;
const double FLYING_ENEMY_FRAME_WIDTH = 64.25;
const double FLYING_ENEMY_FRAME_HEIGHT = 30;

const double PLAY_BUTON_POSX = 390;
const double PLAY_BUTTON_POSY = 180;
const double HELP_BUTTON_POSX = 394;
const double HELP_BUTTON_POSY = 260;
const double OPTION_BUTTON_POSX = 340;
const double OPTION_BUTTON_POSY = 340;
const double EXIT_BUTTON_POSX = 400;
const double EXIT_BUTTON_POSY = 420;
const double EXIT_OPTION_BUTTON_POSX = 443;
const double EXIT_OPTION_BUTTON_POSY = 470.00;
const double HARD_MODE_BUTTON_POSX = 338.50;
const double HARD_MODE_BUTTON_POSY = 260.50;
const double EASY_MODE_BUTTON_POSX = 339.00;
const double EASY_MODE_BUTTON_POSY = 173.50;
const double BACK_BUTTON_POSX = 31;
const double BACK_BUTTON_POSY = 470;
const double PAUSE_BUTTON_POSX = 31;
const double PAUSE_BUTTON_POSY = 29;
const double CONTINUE_BUTTON_POSX = 31;
const double CONTINUE_BUTTON_POSY = 29;
const double LIVES_POSX = 100;
const double LIVES_POSY = 29;
const double CHOOSE_SONIC_BUTTON_POSX = 36;
const double CHOOSE_SONIC_BUTTON_POSY = 80;
const double CHOOSE_SHADOW_BUTTON_POSX = 630;
const double CHOOSE_SHADOW_BUTTON_POSY = 80;


const int TEXT_1_POSX = 670;
const int TEXT_1_POSY = 20;
const int TEXT_2_POSX = 670;
const int TEXT_2_POSY = 80;
const int SCORE_POSX = 845;
const int SCORE_POSY = 20;
const int HIGH_SCORE_POSX = 840;
const int HIGH_SCORE_POSY = 80;

const double LAYER_SPEED = 1.5;
const int RUNNING_FRAMES = 4;
const int FLYING_ENEMY_FRAMES = 4;
const int GROUND_ENEMY_FRAMES = 4;


void LogError(std::string msg, int error_code = SDL_ERROR);

#endif // !GAME_LIB_