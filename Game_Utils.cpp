#include "Game_Utils.h"

std::string GetHighScoreFromFile(std::string path)
{
	std::fstream HighScoreFile;
	std::string highscore;

	HighScoreFile.open(path, std::ios::in);
	HighScoreFile >> highscore;

	return highscore;
}

void UpdateHighScore(std::string path,
	const int& score, 
	const std::string& old_high_score)
{
	int oldHighScore = 0;
	std::fstream HighScoreFile;
	std::string newHighScore;
	std::stringstream ConvertToInt(old_high_score);

	HighScoreFile.open(path, std::ios::out);

	ConvertToInt >> oldHighScore;
	if (score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	HighScoreFile << newHighScore;
}

int UpdateGameTimeAndScore(
	int& time,
	int& speed,
	int& score)
{
	if (time == TIME_MAX)// bằng timeMax sẽ tăng tốc độ
	{
		speed += SPEED_INCREASEMENT;
	}

	if (time > TIME_MAX)// set time về 0 để tính lại từ đầu
	{
		time = 0;
	}
	if (time % 5 == 0)// cứ 5 time thì có 1 điểm
	{
		score += SCORE_INCREASEMENT;
	}
	
	time += TIME_INCREASEMENT;

	return time;
}

//Render 2 ảnh, 1 ảnh bắt đàu ở 1 vị trí âm, ảnh sau bắt đầu ở vị trí của ảnh trước cộng chiều rộng 
void RenderScrollingBackground(double& offsetSpeed,
	LTexture (&gBackgroundTexture),
	SDL_Renderer* gRenderer)
{
	double layer_speed = LAYER_SPEED;
	//offsetSpeed is decreased by a constant speed value layer_speed each frame, causing the background texture to move to the left.
	offsetSpeed -= layer_speed;

	//Once offsetSpeed is less than the negative width of the gBackgroundTexture,
	//we know that the texture has fully scrolled off the screen to the left.
	if (offsetSpeed < -gBackgroundTexture.GetWidth())
	{
		offsetSpeed = 0;
	}
	gBackgroundTexture.Render(               offsetSpeed                 , 0, gRenderer);
	gBackgroundTexture.Render(offsetSpeed + gBackgroundTexture.GetWidth(), 0, gRenderer);
	
}
//Render 2 ảnh, 1 ảnh bắt đàu ở 1 vị trí âm, ảnh sau bắt đầu ở vị trí của ảnh trước cộng chiều rộng
//Ground speed sẽ bằng tốc độ chạy của nvat
void RenderScrollingGround(int& offsetSpeed,
	const int acceleration,
	LTexture gGroundTexture,
	SDL_Renderer* gRenderer)
{
	offsetSpeed -= GROUND_SPEED + acceleration;
	if (offsetSpeed < -gGroundTexture.GetWidth())
	{
		offsetSpeed = 0;
	}
	gGroundTexture.Render(        offsetSpeed                    , 0, gRenderer);
	gGroundTexture.Render(offsetSpeed + gGroundTexture.GetWidth(), 0, gRenderer);
}

//set tình trạng của button và render
void HandlePlayButton(SDL_Event* e,
    SDL_Rect(&gChooseSonicButton)[BUTTON_TOTAL],
    SDL_Rect(&gChooseShadowButton)[BUTTON_TOTAL],
    Button& PlayButton,
    Button& ChooseSonicButton,
    Button& ChooseShadowButton,
    LTexture gChooseSonicButtonTexture,
    LTexture gChooseShadowButtonTexture,
    LTexture gChooseCharacterBackGroundTexture,
	LTexture& gCharacterTexture,
	LTexture& gSonicTexture,
	LTexture& gShadowTexture,
    SDL_Renderer* gRenderer,
    bool& QuitMenu,
    bool& Play,
    Mix_Chunk* gClick)
{
	if (PlayButton.IsInside(PLAY_BUTON))// check if the mouse is inside the button
	{
		switch (e->type)
		{
		default:
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:// if inside playbutton and click
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;

			bool ChooseDone = false;
			while (!ChooseDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ChooseDone = true;
						QuitMenu = true;
					}

					if (ChooseSonicButton.IsInside(CHOOSE_CHARACTER_BUTTON))
					{
						switch (e->type)
						{
						default:
							ChooseSonicButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							ChooseSonicButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							gCharacterTexture = gSonicTexture;
							ChooseDone = true;
							QuitMenu = true;
							Play = true;
							break;
						}
					}
					else
					{
						ChooseSonicButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					if (ChooseShadowButton.IsInside(CHOOSE_CHARACTER_BUTTON))
					{
						switch (e->type)
						{
						default:
							ChooseShadowButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							ChooseShadowButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							gCharacterTexture = gShadowTexture;
							ChooseDone = true;
							QuitMenu = true;
							Play = true;
							break;
						}
					}
					else
					{
						ChooseShadowButton.currentSprite = BUTTON_MOUSE_OUT;
					}
					
					gChooseCharacterBackGroundTexture.Render(0, 0, gRenderer);

					SDL_Rect* currentClip_ChooseSonic = &gChooseSonicButton[ChooseSonicButton.currentSprite];
					ChooseSonicButton.Render(currentClip_ChooseSonic, gRenderer, gChooseSonicButtonTexture);

					SDL_Rect* currentClip_ChooseShadow = &gChooseShadowButton[ChooseShadowButton.currentSprite];
					ChooseShadowButton.Render(currentClip_ChooseShadow, gRenderer, gChooseShadowButtonTexture);

					SDL_RenderPresent(gRenderer);

				} while ((SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
			}
			
			break;
		}
	}
	else
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

//set tình trạng của button và render
void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quit_Menu, 
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(HELP_BUTTON))
	{
		switch (e->type)
		{
		default:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool ReadDone = false;
			// instruction loop
			while (!ReadDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						ReadDone = true;
						Quit_Menu = true;
					}
					if (BackButton.IsInside(BACK_BUTTON))
					{
						switch (e->type)
						{
						default:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer);
					
					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);
					
					SDL_RenderPresent(gRenderer);
				} while ((SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}else
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

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
	Mix_Chunk *gClick)
{
	if (OptionButton.IsInside(OPTION_BUTTON))
	{
		switch (e->type)
		{
		default:
			OptionButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			OptionButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);

			bool SetUpDone = false;
			// instruction loop
			while (!SetUpDone)
			{
				do
				{
					if (e->type == SDL_QUIT)
					{
						SetUpDone = true;
						Quit_Menu = true;
					}
					if (ExitOptionButton.IsInside(EXIT_OPTION_BUTTON))
					{
						switch (e->type)
						{
						default:
							ExitOptionButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:
							ExitOptionButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							SetUpDone = true;
							break;
						}
					}
					else
					{
						ExitOptionButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					if (HardModeButton.IsInside(HARD_MODE_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEBUTTONDOWN:
							HardModeButton.currentSprite = BUTTON_MOUSE_OVER;
							EasyModeButton.currentSprite = BUTTON_MOUSE_OUT;
							gameMode = HARD_MODE;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							break;
						}
					}
	
					if (EasyModeButton.IsInside(EASY_MODE_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEBUTTONDOWN:
							EasyModeButton.currentSprite = BUTTON_MOUSE_OVER;
							HardModeButton.currentSprite = BUTTON_MOUSE_OUT;
							gameMode = EASY_MODE;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							break;
						}
					}

					gOptionTexture.Render(327.00, 131.50, gRenderer);
					
					SDL_Rect* currentClip_Exit = &gExitOptionButton[ExitOptionButton.currentSprite];
					ExitOptionButton.Render(currentClip_Exit, gRenderer, gExitOptionButtonTexture);
					
					SDL_Rect* currentClip_Hard_mode = &gHardModeButton[HardModeButton.currentSprite];
					HardModeButton.Render(currentClip_Hard_mode, gRenderer, gHardModeButtonTexture);

					SDL_Rect* currentClip_Easy_mode = &gEasyModeButton[EasyModeButton.currentSprite];
					EasyModeButton.Render(currentClip_Easy_mode, gRenderer, gEasyModeButtonTexture);

					SDL_RenderPresent(gRenderer);
				} while ((SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}else
	{
		OptionButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleSoundButton(SDL_Event* e,
    SDL_Rect(&gSoundButton)[BUTTON_TOTAL],
	Button& SoundButton,
	Mix_Chunk*(&gClick),
    Mix_Chunk*(&gJump),
    Mix_Chunk*(&gLose))
{
	if (SoundButton.IsInside(SOUND_BUTTON))
	{
		switch (e->type)
		{
			case SDL_MOUSEBUTTONDOWN:
				if(SoundButton.currentSprite == BUTTON_MOUSE_OVER)
				{
					SoundButton.currentSprite = BUTTON_MOUSE_OUT;
					gClick = nullptr;
					gJump = nullptr;
					gLose = nullptr;
				}
				else if(SoundButton.currentSprite == BUTTON_MOUSE_OUT)
				{
					SoundButton.currentSprite = BUTTON_MOUSE_OVER;
					gClick = Mix_LoadWAV("sound/mouse_click.wav");
					gJump = Mix_LoadWAV("sound/jump_sound.wav");
					gLose = Mix_LoadWAV("sound/lose_sound.wav");
				}
				break;
		}
	}

}

void HandleMusicButton(SDL_Event* e,
    SDL_Rect(&gMusicButton)[BUTTON_TOTAL],
	Button& MusicButton)
{
	if (MusicButton.IsInside(MUSIC_BUTTON))
	{
		switch (e->type)
		{
			case SDL_MOUSEBUTTONDOWN:
				if(MusicButton.currentSprite == BUTTON_MOUSE_OVER)
				{
					MusicButton.currentSprite = BUTTON_MOUSE_OUT;
					Mix_PauseMusic();
				}
				else if(MusicButton.currentSprite == BUTTON_MOUSE_OUT)
				{
					MusicButton.currentSprite = BUTTON_MOUSE_OVER;
					Mix_ResumeMusic();
				}
				break;
		}
	}
}

//set tình trạng của button để render
void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(EXIT_BUTTON))
	{
		switch (e->type)
		{
		default:
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Quit = true;
			ExitButton.currentSprite = BUTTON_MOUSE_OVER;
			Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
			break;
		}
	}
	else
	{
		ExitButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

//set tình trạng của button và render
void HandleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	bool& Quit,
	bool &Play,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		if (e->type == SDL_QUIT)
		{
			Quit = true;
			Play = false;
			break;
		}
		do
		{
			if (ContinueButton.IsInside(PAUSE_AND_CONTINUE_BUTTON))
			{
				switch (e->type)
				{
					default:
						ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
						break;
					case SDL_MOUSEBUTTONDOWN :
					
						ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
						Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
						Mix_ResumeMusic();
						Game_State = true;
						Back_To_Game = true;
					    break;
				}
			}else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);

		} while ((SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
	}
}

//set tình trạng của button để render
void HandlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer, 
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL], 
	Button& PauseButton, 
	Button ContinueButton, 
	LTexture gContinueButtonTexture, 
	bool &Game_State,
	bool &Quit,
	bool &Play,
	Mix_Chunk *gClick)
{
	if (PauseButton.IsInside(PAUSE_AND_CONTINUE_BUTTON))
	{
		switch (e->type)
		{
			case SDL_MOUSEMOTION:
				PauseButton.currentSprite = BUTTON_MOUSE_OVER;
				break;
			case SDL_MOUSEBUTTONDOWN:
				PauseButton.currentSprite = BUTTON_MOUSE_OVER;
				Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
				Mix_PauseMusic();
				break;
			case SDL_MOUSEBUTTONUP:
				Game_State = false;
				HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, 
									gContinueButton, Game_State, Quit, Play, gClick);
				break;
		}
	}
	else
	{
		PauseButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void GenerateEnemy(Enemy& enemy1,
	Enemy& enemy2,
	Enemy& enemy3,
	SDL_Rect(&gFlyingEnemyClips)[FLYING_ENEMY_FRAMES],
	SDL_Rect(&gGroundEnemyClips)[GROUND_ENEMY_FRAMES], 
	SDL_Renderer * gRenderer)
{
	enemy1.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy2.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy3.LoadFromFile("imgs/enemy/bat.png", gRenderer);
	
		gFlyingEnemyClips[0].x = 0;
		gFlyingEnemyClips[0].y = 0;
		gFlyingEnemyClips[0].w = FLYING_ENEMY_FRAME_WIDTH;
		gFlyingEnemyClips[0].h = FLYING_ENEMY_FRAME_HEIGHT;

		gFlyingEnemyClips[1].x = FLYING_ENEMY_FRAME_WIDTH;
		gFlyingEnemyClips[1].y = 0;
		gFlyingEnemyClips[1].w = FLYING_ENEMY_FRAME_WIDTH;
		gFlyingEnemyClips[1].h = FLYING_ENEMY_FRAME_HEIGHT;

		gFlyingEnemyClips[2].x = FLYING_ENEMY_FRAME_WIDTH * 2;
		gFlyingEnemyClips[2].y = 0;
		gFlyingEnemyClips[2].w = FLYING_ENEMY_FRAME_WIDTH;
		gFlyingEnemyClips[2].h = FLYING_ENEMY_FRAME_HEIGHT;

		gFlyingEnemyClips[3].x = FLYING_ENEMY_FRAME_WIDTH * 3;
		gFlyingEnemyClips[3].y = 0;
		gFlyingEnemyClips[3].w = FLYING_ENEMY_FRAME_WIDTH;
		gFlyingEnemyClips[3].h = FLYING_ENEMY_FRAME_HEIGHT;

		gGroundEnemyClips[0].x = 0;
		gGroundEnemyClips[0].y = 0;
		gGroundEnemyClips[0].w = GROUND_ENEMY_FRAME_WIDTH;
		gGroundEnemyClips[0].h = GROUND_ENEMY_FRAME_HEIGHT;

		gGroundEnemyClips[1].x = GROUND_ENEMY_FRAME_WIDTH;
		gGroundEnemyClips[1].y = 0;
		gGroundEnemyClips[1].w = GROUND_ENEMY_FRAME_WIDTH;
		gGroundEnemyClips[1].h = GROUND_ENEMY_FRAME_HEIGHT;

		gGroundEnemyClips[2].x = GROUND_ENEMY_FRAME_WIDTH * 2;
		gGroundEnemyClips[2].y = 0;
		gGroundEnemyClips[2].w = GROUND_ENEMY_FRAME_WIDTH;
		gGroundEnemyClips[2].h = GROUND_ENEMY_FRAME_HEIGHT;

		gGroundEnemyClips[3].x = GROUND_ENEMY_FRAME_WIDTH * 3;
		gGroundEnemyClips[3].y = 0;
		gGroundEnemyClips[3].w = GROUND_ENEMY_FRAME_WIDTH;
		gGroundEnemyClips[3].h = GROUND_ENEMY_FRAME_HEIGHT;

}

void GeneratePowerUp(PowerUp &power,
    SDL_Renderer* gRenderer, int type)
{
	if(type == SHIELD)power.LoadFromFile("imgs/other/shield.png", gRenderer);
	else if(type == LIVE)power.LoadFromFile("imgs/other/1lives.png", gRenderer);
}

bool CheckColission(Character character,
	SDL_Rect* char_clip,
	Enemy enemy, 
	SDL_Rect* enemy_clip)
{
	bool collide = false;

	if (enemy.GetType() == ON_GROUND_ENEMY)
	{

		double distance = (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2)) *  (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2))
						+ (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2)) *  (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2));

		if(distance <= 1200)collide = true;
	}
	else if(enemy.GetType() == IN_AIR_ENEMY)
	{
		double distance = (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2)) *  (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2))
						+ (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2)) *  (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2));

		if(distance <= 1550)collide = true;
	}

	return collide;
}

bool CheckEnemyColission(Character character,
	Enemy enemy1,
	Enemy enemy2, 
	Enemy enemy3,
	SDL_Rect* char_clip,
	SDL_Rect* FlyingEnemy_clip,
	SDL_Rect* GroundEnemy_clip1,
	SDL_Rect* GroundEnemy_clip2
	)
{
	if (CheckColission(character, char_clip, enemy1, GroundEnemy_clip1))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy2, GroundEnemy_clip2))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy3, FlyingEnemy_clip))
	{
		return true;
	}
	return false;
}

bool CheckPowerUpColission(Character character,
    SDL_Rect* char_clip,
    PowerUp (&shield))
{
	bool collide = false;
	double distance = (character.GetPosX() + char_clip->w/2 - shield.GetPosX() - shield.GetWidth()) *  (character.GetPosX() + char_clip->w/2 - shield.GetPosX() - shield.GetWidth())
					+ (character.GetPosY() + char_clip->w/2 - shield.GetPosY() - shield.GetWidth()) *  (character.GetPosY() + char_clip->w/2 - shield.GetPosY() - shield.GetWidth());
	if(distance <= 1550)collide = true;
return collide;
}

void ControlCharFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_CHAR >= RUNNING_FRAMES)
	{
		frame = 0;
	}
}

void ControlEnemyFrame(int &frame)
{
	frame += FRAME_INCREASEMENT;
	if (frame / SLOW_FRAME_ENEMY >= FLYING_ENEMY_FRAMES)
	{
		frame = 0;
	}
}

void DrawPlayerScore(LTexture gTextTexture,
	LTexture gScoreTexture,
	SDL_Color textColor,
	SDL_Renderer *gRenderer,
	TTF_Font *gFont, 
	const int& score)
{
	gTextTexture.Render(TEXT_1_POSX, TEXT_1_POSY, gRenderer);
	if (gScoreTexture.LoadFromRenderedText(std::to_string(score), gFont, textColor, gRenderer))
	{
		gScoreTexture.Render(SCORE_POSX, SCORE_POSY, gRenderer);
	}
}

void DrawPlayerHighScore(LTexture gTextTexture,
	LTexture gHighScoreTexture, 
	SDL_Color textColor, 
	SDL_Renderer* gRenderer, 
	TTF_Font* gFont, 
	const std::string& HighScore)
{
	gTextTexture.Render(TEXT_2_POSX, TEXT_2_POSY, gRenderer);
	if (gHighScoreTexture.LoadFromRenderedText(HighScore, gFont, textColor, gRenderer))
	{
		gHighScoreTexture.Render(HIGH_SCORE_POSX, HIGH_SCORE_POSY, gRenderer);
	}
}

bool AskToPlayAgain(LTexture gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool &Play,
	bool &Quit_Menu)
{
	bool Play_Again = false;
	if (Play)
	{
		bool End_Of_Selection_State = false;
		while (!End_Of_Selection_State)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play = false;
					End_Of_Selection_State = true;
					return false;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Of_Selection_State = true;
						Play_Again = true;
						break;
					case SDLK_ESCAPE:
						End_Of_Selection_State = true;
						Play = false;
						Quit_Menu = false;
						break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
return Play_Again;
}
