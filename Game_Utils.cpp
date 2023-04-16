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

void RenderScrollingBackground(double& offsetSpeed,
	LTexture &gBackgroundTexture,
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
	gBackgroundTexture.Render(offsetSpeed, 0, gRenderer);
	gBackgroundTexture.Render(offsetSpeed + gBackgroundTexture.GetWidth(), 0, gRenderer);
	
}

void RenderScrollingGround(int& speed,
	const int acceleration,
	LTexture gGroundTexture,
	SDL_Renderer* gRenderer)
{
	speed -= GROUND_SPEED + acceleration;
	if (speed < -gGroundTexture.GetWidth())
	{
		speed = 0;
	}
	gGroundTexture.Render(speed, 0, gRenderer);
	gGroundTexture.Render(speed + gGroundTexture.GetWidth(), 0, gRenderer);
}

void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (e->type == SDL_QUIT)
	{
		QuitMenu = true;
	}

	if (PlayButton.IsInside(e, COMMON_BUTTON))// check if the mouse is inside the button
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION: // if inside playbutton and moving, button over
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:// if inside playbutton and click
			Play = true;
			QuitMenu = true;
			Mix_PlayChannel(MIX_CHANNEL, gClick, 0);
			PlayButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		}
	}
	else// if the mouse is outside the button
	{
		PlayButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleHelpButton(SDL_Event* e,
	SDL_Rect(&gBackButton)[BUTTON_TOTAL],
	Button& HelpButton, 
	Button& BackButton, 
	LTexture gInstructionTexture,
	LTexture gBackButtonTexture, 
	SDL_Renderer *gRenderer, 
	bool &Quit_game, 
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))// check if the mouse is inside the help button
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:// if inside help button and moving, button over
			HelpButton.currentSprite = BUTTON_MOUSE_OVER;
			break;
		case SDL_MOUSEBUTTONDOWN:// if inside help button and click
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
						Quit_game = true;
						Close();
					}
					else if (BackButton.IsInside(e, BACK_BUTTON))
					{
						switch (e->type)
						{
						case SDL_MOUSEMOTION:// if inside playbutton and moving, button over
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							break;
						case SDL_MOUSEBUTTONDOWN:// if inside playbutton and click
							BackButton.currentSprite = BUTTON_MOUSE_OVER;
							Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
							ReadDone = true;
							break;
						}
					}
					else// if the mouse is outside the back button
					{
						BackButton.currentSprite = BUTTON_MOUSE_OUT;
					}

					gInstructionTexture.Render(0, 0, gRenderer); // Render instruction texture, gInstructionTexture was init in Loadfunction in main
					
					SDL_Rect* currentClip_Back = &gBackButton[BackButton.currentSprite];
					BackButton.Render(currentClip_Back, gRenderer, gBackButtonTexture);
					
					SDL_RenderPresent(gRenderer);
				} while ((SDL_PollEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
			}
			break;
		}
	}
	else// if the mouse is outside the help button
	{
		HelpButton.currentSprite = BUTTON_MOUSE_OUT;
	}
}

void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
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

void HandleContinueButton(Button ContinueButton,
	LTexture gContinueButtonTexture,
	SDL_Event* e,
	SDL_Renderer* gRenderer,
	SDL_Rect(&gContinueButton)[BUTTON_TOTAL],
	bool& Game_State,
	Mix_Chunk* gClick)
{
	bool Back_To_Game = false;
	while (!Back_To_Game)
	{
		do
		{
			if (ContinueButton.IsInside(e, SMALL_BUTTON))
			{
				switch (e->type)
				{
					case SDL_MOUSEMOTION:
						ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
						break;
					case SDL_MOUSEBUTTONDOWN :
					{
						ContinueButton.currentSprite = BUTTON_MOUSE_OVER;
						Mix_PlayChannel(MIX_CHANNEL, gClick, NOT_REPEATITIVE);
						Mix_ResumeMusic();
						Game_State = true;
						Back_To_Game = true;
					}
					break;
				}
			}
			else
			{
				ContinueButton.currentSprite = BUTTON_MOUSE_OUT;
			}
		
			SDL_Rect* currentClip_Continue = &gContinueButton[ContinueButton.currentSprite];
			ContinueButton.Render(currentClip_Continue, gRenderer, gContinueButtonTexture);

			SDL_RenderPresent(gRenderer);
		} while ((SDL_WaitEvent(e) != 0 && e->type == SDL_MOUSEBUTTONDOWN) || e->type == SDL_MOUSEMOTION);
	}
}

void HandlePauseButton(SDL_Event* e,
	SDL_Renderer* gRenderer, 
	SDL_Rect (&gContinueButton)[BUTTON_TOTAL], 
	Button& PauseButton, 
	Button ContinueButton, 
	LTexture gContinueButtonTexture, 
	bool &Game_State, 
	Mix_Chunk *gClick)
{
	if (PauseButton.IsInside(e, SMALL_BUTTON))
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
				HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, gClick);
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
	SDL_Rect(&gEnemyClips)[FLYING_FRAMES], 
	SDL_Renderer * gRenderer)
{
	enemy1.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy2.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy3.LoadFromFile("imgs/enemy/bat.png", gRenderer);
	{
		gEnemyClips[0].x = 43 * 3;
		gEnemyClips[0].y = 0;
		gEnemyClips[0].w = 43;
		gEnemyClips[0].h = 30;

		gEnemyClips[1].x = 43 * 4;
		gEnemyClips[1].y = 0;
		gEnemyClips[1].w = 43;
		gEnemyClips[1].h = 30;

		gEnemyClips[2].x = 43 * 2;
		gEnemyClips[2].y = 0;
		gEnemyClips[2].w = 43;
		gEnemyClips[2].h = 30;

		gEnemyClips[3].x = 43;
		gEnemyClips[3].y = 0;
		gEnemyClips[3].w = 43;
		gEnemyClips[3].h = 30;

		gEnemyClips[4].x = 0;
		gEnemyClips[4].y = 0;
		gEnemyClips[4].w = 43;
		gEnemyClips[4].h = 30;
	}
}

bool CheckColission(Character character,
	SDL_Rect* char_clip,
	Enemy enemy, 
	SDL_Rect* enemy_clip)
{
	bool collide = false;

	if (enemy.GetType() == ON_GROUND_ENEMY)
	{

		double distance = (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - enemy.GetWidth()/2) *  (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - enemy.GetWidth()/2)
						+ (character.GetPosY() + (char_clip->h/2) - enemy.GetPosY() - (enemy.GetHeight()/2)) *  (character.GetPosY() + (char_clip->h/2) - enemy.GetPosY() - (enemy.GetHeight()/2));

		if(distance <= 1000)collide = true;
	}
	else
	{
		double distance = (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2)) *  (character.GetPosX() + (char_clip->w/2) - enemy.GetPosX() - (enemy_clip->w/2))
						+ (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2)) *  (character.GetPosY() + (char_clip->w/2) - enemy.GetPosY() - (enemy_clip->w/2));

		if(distance <= 444)collide = true;
	}

	return collide;
}

bool CheckEnemyColission(Character character,
	Enemy enemy1,
	Enemy enemy2, 
	Enemy enemy3,
	SDL_Rect* char_clip,
	SDL_Rect* enemy_clip
	)
{
	if (CheckColission(character, char_clip, enemy1))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy2))
	{
		return true;
	}
	if (CheckColission(character, char_clip, enemy3, enemy_clip))
	{
		return true;
	}
	return false;
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
	if (frame / SLOW_FRAME_ENEMY >= FLYING_FRAMES)
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

void DrawEndGameSelection(LTexture gLoseTexture,
	SDL_Event *e, 
	SDL_Renderer *gRenderer,
	bool &Play_Again)
{
	if (Play_Again)
	{
		bool End_Game = false;
		while (!End_Game)
		{
			while (SDL_PollEvent(e) != 0)
			{
				if (e->type == SDL_QUIT)
				{
					Play_Again = false;
					End_Game = true;
					return;
				}

				if (e->type == SDL_KEYDOWN)
				{
					switch (e->key.keysym.sym)
					{
					case SDLK_SPACE:
						End_Game = true;
						break;
					case SDLK_ESCAPE:
						End_Game = true;
						Play_Again = false;
						break;
					}
				}
			}

			gLoseTexture.Render(0, 0, gRenderer);

			SDL_RenderPresent(gRenderer);
		}
	}
}