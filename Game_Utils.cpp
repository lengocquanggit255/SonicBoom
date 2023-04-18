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

//set tình trạng của button để render
void HandlePlayButton(SDL_Event* e,
	Button& PlayButton,
	bool& QuitMenu,
	bool& Play,
	Mix_Chunk* gClick)
{
	if (PlayButton.IsInside(e, COMMON_BUTTON))// check if the mouse is inside the button
	{
		switch (e->type)
		{
		default:
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
	bool &Quit_game, 
	Mix_Chunk *gClick)
{
	if (HelpButton.IsInside(e, COMMON_BUTTON))
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
						Quit_game = true;
					}
					else if (BackButton.IsInside(e, BACK_BUTTON))
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

//set tình trạng của button để render
void HandleExitButton(SDL_Event* e,
	Button& ExitButton,
	bool& Quit,
	Mix_Chunk* gClick)
{
	if (ExitButton.IsInside(e, COMMON_BUTTON))
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
			if (ContinueButton.IsInside(e, SMALL_BUTTON))
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
				HandleContinueButton(ContinueButton, gContinueButtonTexture, e, gRenderer, gContinueButton, Game_State, Quit, Play, gClick);
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
	SDL_Rect(&gEnemyClips)[FLYING_ENEMY_FRAMES],
	SDL_Rect(&gGroundEnemyClips)[GROUND_ENEMY_FRAMES], 
	SDL_Renderer * gRenderer)
{
	enemy1.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy2.LoadFromFile("imgs/enemy/cactus.png", gRenderer);
	enemy3.LoadFromFile("imgs/enemy/bat.png", gRenderer);
	
		gEnemyClips[0].x = 0;
		gEnemyClips[0].y = 0;
		gEnemyClips[0].w = 64.25;
		gEnemyClips[0].h = 30;

		gEnemyClips[1].x = 64.25;
		gEnemyClips[1].y = 0;
		gEnemyClips[1].w = 64.25;
		gEnemyClips[1].h = 30;

		gEnemyClips[2].x = 64.25 * 2;
		gEnemyClips[2].y = 0;
		gEnemyClips[2].w = 64.25;
		gEnemyClips[2].h = 30;

		gEnemyClips[3].x = 64.25 * 3;
		gEnemyClips[3].y = 0;
		gEnemyClips[3].w = 64.25;
		gEnemyClips[3].h = 30;

		gGroundEnemyClips[0].x = 0;
		gGroundEnemyClips[0].y = 0;
		gGroundEnemyClips[0].w = 29.25;
		gGroundEnemyClips[0].h = 57;

		gGroundEnemyClips[1].x = 29.25;
		gGroundEnemyClips[1].y = 0;
		gGroundEnemyClips[1].w = 29.25;
		gGroundEnemyClips[1].h = 57;

		gGroundEnemyClips[2].x = 29.25 * 2;
		gGroundEnemyClips[2].y = 0;
		gGroundEnemyClips[2].w = 29.25;
		gGroundEnemyClips[2].h = 57;

		gGroundEnemyClips[3].x = 29.25 * 3;
		gGroundEnemyClips[3].y = 0;
		gGroundEnemyClips[3].w = 29.25;
		gGroundEnemyClips[3].h = 57;

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
