#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include "Game_Base.h"
#include "Button.h"
#include "Enemy.h"
#include "Character.h"
#include "PowerUp.h"

std::string GetHighScoreFromFile(std::string path);

void UpdateHighScore(std::string path,
    const int& score, 
    const std::string& old_high_score);

int UpdateGameTimeAndScore(int& time, int& speed, int& score);

void RenderScrollingBackground(double& offsetSpeed,
    LTexture(&gBackgroundTexture),
    SDL_Renderer* gRenderer);

void RenderScrollingGround(int& speed,
    const int acceleration,
    LTexture gGroundTexture,
    SDL_Renderer* gRenderer);

void HandlePlayButton(SDL_Event* e,
    SDL_Rect(&gChooseSonicButton)[BUTTON_TOTAL],
    SDL_Rect(&gChooseShadowButton)[BUTTON_TOTAL],
    Button& PlayButton,
    Button& ChooseSonicButton,
    Button& ChooseShawdownButton,
    LTexture gChooseSonicButtonTexture,
    LTexture gChooseShadowButtonTexture,
    LTexture gChooseCharacterBackGroundTexture,
    LTexture& gCharacterTexture,
	LTexture& gSonicTexture,
	LTexture& gShadowTexture,
    SDL_Renderer* gRenderer,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* gClick);

void HandleHelpButton(SDL_Event* e,
    SDL_Rect(&gBackButton)[BUTTON_TOTAL],
    Button& HelpButton,
    Button& BackButton,
    LTexture gInstructionTexture,
    LTexture gBackButtonTexture,
    SDL_Renderer* gRenderer,
    bool& Quit_game,
    Mix_Chunk* gClick);

void HandleOptionButton (SDL_Event* e,
	SDL_Rect(&gExitOptionButton)[BUTTON_TOTAL],
	SDL_Rect(&gHardModeButton)[BUTTON_TOTAL],
	SDL_Rect(&gEasyModeButton)[BUTTON_TOTAL],
	Button& OptionButton,
	Button& HardModeButton,
	Button& EasyModeButton,
	Button& ExitOptionButton, 
	LTexture gOptionTexture,
	LTexture gHardModeButtonTexture,
	LTexture gEasyModeButtonTexture,
	LTexture gExitOptionButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quit_Menu, 
    int &gameMode,
	Mix_Chunk *gClick);

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit_Menu,
	Mix_Chunk* gClick);

void HandleSoundButton(SDL_Event* e,
    SDL_Rect(&gSoundButton)[BUTTON_TOTAL],
	Button& SoundButton,
	Mix_Chunk*(&gClick),
    Mix_Chunk*(&gJump),
    Mix_Chunk*(&gLose));

void HandleMusicButton(SDL_Event* e,
    SDL_Rect(&gMusicButton)[BUTTON_TOTAL],
	Button& MusicButton);

void HandleContinueButton(Button ContinueButton,
    LTexture gContinueButtonTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    bool& Game_State,
    bool& Die,
    bool &Play,
    Mix_Chunk* gClick);

void HandlePauseButton(SDL_Event* e,
    SDL_Renderer* gRenderer,
    SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
    Button& PauseButton,
    Button ContinueButton,
    LTexture gContinueButtonTexture,
    bool& game_state,
    bool& Die,
    bool &Play,
    Mix_Chunk* gClick);

void GenerateEnemy(Enemy& enemy1,
    Enemy& enemy2,
    Enemy& enemy3,
    SDL_Rect(&gFlyingEnemyClips)[FLYING_ENEMY_FRAMES],
    SDL_Rect(&gGroundEnemyClips)[GROUND_ENEMY_FRAMES],
    SDL_Renderer* gRenderer);

void GeneratePowerUp(PowerUp &power,
    SDL_Renderer* gRenderer, int type);

bool CheckColission(Character character,
    SDL_Rect* char_clip,
    Enemy enemy,
    SDL_Rect* enemy_clip = nullptr);

bool CheckEnemyColission(Character character,
    Enemy enemy1,
    Enemy enemy2,
    Enemy enemy3,
    SDL_Rect* char_clip,
    SDL_Rect* FlyingEnemy_clip = nullptr,
    SDL_Rect* GroundEnemy_clip1 = nullptr,
    SDL_Rect* GroundEnemy_clip2 = nullptr);

bool CheckPowerUpColission(Character character,
    SDL_Rect* char_clip,
    PowerUp (&power));

void ControlCharFrame(int& frame);

void ControlEnemyFrame(int& frame);

void DrawPlayerScore(LTexture gTextTexture,
    LTexture gScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont,
    const int& score);

void DrawPlayerHighScore(LTexture gTextTexture,
    LTexture gHighScoreTexture,
    SDL_Color textColor,
    SDL_Renderer* gRenderer,
    TTF_Font* gFont, 
    const std::string& HighScore);

bool AskToPlayAgain(LTexture gLoseTexture,
    SDL_Event* e,
    SDL_Renderer* gRenderer,
    bool& Play,
    bool &Quit_Menu);

#endif // !GAME_UTILS_H_