#ifndef GAME_H_
#define GAME_H_

#include "Game_Base.h"
#include "Game_Utils.h"
#include "LTexture.h"
#include "Button.h"
#include "Character.h"
#include "Enemy.h"

class Game
{
public:
    bool Init();
    bool LoadMedia();
    bool isRunning(){return running;}
    void gameLoop();
    void ResetGame();
    void Close();

    bool Quit_Menu = false;
    bool Play = false;
   
    bool Die = false;
	bool Game_State = true;
    int	currentTime = 0;
    int score = 0;
    int acceleration = 0;
    int frame_Character = 0;
    int frame_Enemy = 0;

    int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
	double OffsetSpeed_Bkgr = BASE_OFFSET_SPEED;
    
    int lives = 3;

    std::string highscore = GetHighScoreFromFile("high_score.txt");

private:
    bool running = false;
};

#endif