#include "Game.h"

const std::string LAYER = {
	"imgs/background/layer.jpg",
};

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr; //Renderer for everything
SDL_Color textColor = { 0, 0, 0 };
TTF_Font* gFont = nullptr;
Mix_Music* gMusic = nullptr;
Mix_Music* gMenuMusic = nullptr;
Mix_Chunk* gClick = nullptr;
Mix_Chunk* gJump = nullptr;
Mix_Chunk* gLose = nullptr;

SDL_Rect gPlayButton[BUTTON_TOTAL];
SDL_Rect gHelpButton[BUTTON_TOTAL];
SDL_Rect gExitButton[BUTTON_TOTAL];
SDL_Rect gBackButton[BUTTON_TOTAL];
SDL_Rect gPauseButton[BUTTON_TOTAL];
SDL_Rect gContinueButton[BUTTON_TOTAL];
SDL_Rect gPlayAgainButton[BUTTON_TOTAL];
SDL_Rect gChooseSonicButton[BUTTON_TOTAL];
SDL_Rect gChooseShadowButton[BUTTON_TOTAL];
SDL_Rect gCharacterClips[RUNNING_FRAMES];
SDL_Rect gFlyingEnemyClips[FLYING_ENEMY_FRAMES];
SDL_Rect gGroundEnemyClips[GROUND_ENEMY_FRAMES];

LTexture gMenuTexture;
LTexture gInstructionTexture;
LTexture gBackgroundTexture;
LTexture gCharacterTexture;
LTexture gSonicTexture;
LTexture gShadowTexture;
LTexture gGroundTexture;
LTexture gPlayButtonTexture;
LTexture gHelpButtonTexture;
LTexture gExitButtonTexture;
LTexture gBackButtonTexture;
LTexture gPauseButtonTexture;
LTexture gContinueButtonTexture;
LTexture gChooseSonicButtonTexture;
LTexture gChooseShadowButtonTexture;
LTexture gChooseCharacterBackGroundTexture;
LTexture gLoseTexture;
LTexture gText1Texture;
LTexture gScoreTexture;
LTexture gText2Texture;
LTexture gHighScoreTexture;

Button PlayButton(PLAY_BUTON_POSX, PLAY_BUTTON_POSY);
Button HelpButton(HELP_BUTTON_POSX, HELP_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button BackButton(BACK_BUTTON_POSX, BACK_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button ChooseSonicButton(CHOOSE_SONIC_BUTTON_POSX, CHOOSE_SONIC_BUTTON_POSY);
Button ChooseShawdownButton(CHOOSE_SHADOW_BUTTON_POSX, CHOOSE_SHADOW_BUTTON_POSY);

Character character;

void Game :: gameLoop()
{
    if(!Init())printf("Failed to initialize!\n");
	else std::cout << "Succeeded to initialize" << std::endl;
	
	if (!LoadMedia())printf("Failed to load media!\n");
	else std::cout << "Succeeded to load media" << std::endl;

	
	Mix_PlayMusic(gMenuMusic, IS_REPEATITIVE);// play menu music
	while (!Quit_Menu)
	{
		SDL_Event e_mouse;
		while (SDL_PollEvent(&e_mouse) != 0)
		{
			if (e_mouse.type == SDL_QUIT)
			{
				Quit_Menu = true;
				Play = false;
			}

			HandlePlayButton(&e_mouse, gChooseSonicButton, gChooseShadowButton, PlayButton,
								ChooseSonicButton, ChooseShawdownButton, gChooseSonicButtonTexture,
								gChooseShadowButtonTexture, gChooseCharacterBackGroundTexture,
								gCharacterTexture, gSonicTexture, gShadowTexture,
								gRenderer, Quit_Menu, Play, gClick);
				
			HandleHelpButton(&e_mouse, gBackButton,
								HelpButton, BackButton, 
								gInstructionTexture, gBackButtonTexture,
								gRenderer, Quit_Menu, gClick);

			HandleExitButton(&e_mouse, ExitButton, Quit_Menu, gClick);
		}

		gMenuTexture.Render(0, 0, gRenderer);
		SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
		PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);

		SDL_Rect* currentClip_Help = &gHelpButton[HelpButton.currentSprite];
		HelpButton.Render(currentClip_Help, gRenderer, gHelpButtonTexture);

		SDL_Rect* currentClip_Exit = &gExitButton[ExitButton.currentSprite];
		ExitButton.Render(currentClip_Exit, gRenderer, gExitButtonTexture);

		SDL_RenderPresent(gRenderer); //present the rendered textures to the screen
	}

	while (Play)// handle play again
	{
		srand(time(NULL));

		SDL_Event e;
		Enemy enemy1(ON_GROUND_ENEMY);
		Enemy enemy2(ON_GROUND_ENEMY);
		Enemy enemy3(IN_AIR_ENEMY);
		
		Mix_PlayMusic(gMusic, IS_REPEATITIVE);
		GenerateEnemy(enemy1, enemy2, enemy3, gFlyingEnemyClips, gGroundEnemyClips, gRenderer);

		//refers to the rate at which an object's position changes over time
		int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
		double OffsetSpeed_Bkgr = BASE_OFFSET_SPEED;				

		while (!Quit)
		{
			if (Game_State)
			{
				UpdateGameTimeAndScore(currentTime, acceleration, score);

				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT)
					{
						Quit = true;
						Play = false;
					}

					HandlePauseButton(&e, gRenderer, gContinueButton,
						PauseButton, ContinueButton,
						gContinueButtonTexture, Game_State, Quit, Play, gClick);

					character.HandleEvent(e, gJump);//change the status to jump
				}

				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
				RenderScrollingGround(OffsetSpeed_Ground, acceleration, gGroundTexture, gRenderer);

				character.Move();

				SDL_Rect* currentClip_Character = nullptr;

				currentClip_Character = &gCharacterClips[frame_Character / SLOW_FRAME_CHAR];
				character.Render(currentClip_Character, gRenderer, gCharacterTexture);

				SDL_Rect* currentClip_GroundEnemy1 = &gGroundEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
				enemy1.Move(acceleration);
				enemy1.Render(gRenderer, currentClip_GroundEnemy1);

				SDL_Rect* currentClip_GroundEnemy2 = &gGroundEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
				enemy2.Move(acceleration);
				enemy2.Render(gRenderer, currentClip_GroundEnemy2);

				SDL_Rect* currentClip_FlyingEnemy = &gFlyingEnemyClips[frame_Enemy / SLOW_FRAME_ENEMY];
				enemy3.Move(acceleration);
				enemy3.Render(gRenderer, currentClip_FlyingEnemy);


				SDL_Rect* currentClip_Pause = &gPauseButton[PauseButton.currentSprite];
				PauseButton.Render(currentClip_Pause, gRenderer, gPauseButtonTexture);


				DrawPlayerScore(gText1Texture, gScoreTexture, textColor, gRenderer, gFont, score);
				DrawPlayerHighScore(gText2Texture, gHighScoreTexture, textColor, gRenderer, gFont, highscore);

				if (CheckEnemyColission(character,
					enemy1, enemy2, enemy3,
					currentClip_Character, currentClip_FlyingEnemy, currentClip_GroundEnemy1, currentClip_GroundEnemy2))
				{
					Mix_PauseMusic();
					Mix_PlayChannel(MIX_CHANNEL, gLose, NOT_REPEATITIVE);
					UpdateHighScore("high_score.txt", score, highscore);
					Quit = true;
				}


				SDL_RenderPresent(gRenderer);// Present tất cả những cái ở phía trên

				ControlCharFrame(frame_Character);
				ControlEnemyFrame(frame_Enemy);
			}
		}

		DrawEndGameSelection(gLoseTexture, &e, gRenderer, Play);
		if (!Play)
		{
			enemy1.~Enemy();
			enemy2.~Enemy();
			enemy3.~Enemy();
		}
	}
	Close();
    return;
}

bool Game::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_VIDEO) < 0)
	{
		LogError("Can not initialize SDL.", SDL_ERROR);
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled!";
		}

		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			LogError("Can not create window", SDL_ERROR);
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				LogError("Can not create renderer", SDL_ERROR);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					LogError("Can not initialize SDL_image", IMG_ERROR);
					success = false;
				}

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game :: LoadMedia()
{
	bool success = true;

	gMusic = Mix_LoadMUS("sound/bkgr_audio.wav");
	if (gMusic == nullptr)
	{
		LogError("Failed to load background music", MIX_ERROR);
		success = false;
	}

	gMenuMusic = Mix_LoadMUS("sound/menu_audio.wav");
	if (gMenuMusic == nullptr)
	{
		LogError("Failed to load menu music", MIX_ERROR);
		success = false;
	}

	gClick = Mix_LoadWAV("sound/mouse_click.wav");
	if (gClick == nullptr)
	{
		LogError("Failed to load mouse click sound", MIX_ERROR);
		success = false;
	}

	gJump = Mix_LoadWAV("sound/jump_sound.wav");
	if (gJump == nullptr)
	{
		LogError("Failed to load jumping sound", MIX_ERROR);
		success = false;
	}

	gLose = Mix_LoadWAV("sound/lose_sound.wav");
	if (gLose == nullptr)
	{
		LogError("Failed to load lose sound", MIX_ERROR);
		success = false;
	}

	else
	{
		gFont = TTF_OpenFont("font/pixel_font.ttf", 28);
		if (gFont == NULL)
		{
			LogError("Failed to load font", MIX_ERROR);
			success = false;
		}
		else
		{
			if (!gText1Texture.LoadFromRenderedText("Your score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text1 texture" << std::endl;
				success = false;
			}

			if (!gText2Texture.LoadFromRenderedText("High score: ", gFont, textColor, gRenderer))
			{
				std::cout << "Failed to render text2 texture" << std::endl;
				success = false;
			}
			
			if (!gMenuTexture.LoadFromFile("imgs/background/menu.png", gRenderer))
			{
				std::cout << "Failed to load menu image" << std::endl;
				success = false;
			}

			if (!gInstructionTexture.LoadFromFile("imgs/background/instruction.png", gRenderer))
			{
				std::cout << "Failed to load instruction image" << std::endl;
				success = false;
			}

			if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png", gRenderer))
			{
				std::cout << "Failed to load play_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)// một mảng chứa từng frame trong clip playButton
				{
					gPlayButton[i].x = COMMON_BUTTON_WIDTH * i; // vị trị frame trong play_button.png
					gPlayButton[i].y = 0;
					gPlayButton[i].w = COMMON_BUTTON_WIDTH;
					gPlayButton[i].h = COMMON_BUTTON_HEIGHT;
				}
			}

			if (!gHelpButtonTexture.LoadFromFile("imgs/button/big_button/help_button.png", gRenderer))
			{
				std::cout << "Failed to load help_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gHelpButton[i].x = COMMON_BUTTON_WIDTH * i;
					gHelpButton[i].y = 0;
					gHelpButton[i].w = COMMON_BUTTON_WIDTH;
					gHelpButton[i].h = COMMON_BUTTON_HEIGHT;
				}
			}

			if (!gBackButtonTexture.LoadFromFile("imgs/button/big_button/back_button.png", gRenderer))
			{
				std::cout << "Failed to load back_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gBackButton[i].x = BACK_BUTTON_WIDTH * i;
					gBackButton[i].y = 0;
					gBackButton[i].w = BACK_BUTTON_WIDTH;
					gBackButton[i].h = BACK_BUTTON_HEIGHT;
				}
			}

			if (!gExitButtonTexture.LoadFromFile("imgs/button/big_button/exit_button.png", gRenderer))
			{
				std::cout << "Failed to load exit_button image" << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gExitButton[i].x = COMMON_BUTTON_WIDTH * i;
					gExitButton[i].y = 0;
					gExitButton[i].w = COMMON_BUTTON_WIDTH;
					gExitButton[i].h = COMMON_BUTTON_HEIGHT;
				}
			}

			if (!gPauseButtonTexture.LoadFromFile("imgs/button/big_button/pause_button.png", gRenderer))
			{
				std::cout << "Failed to load pause_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gPauseButton[i].x = SMALL_BUTTON_WIDTH * i;
					gPauseButton[i].y = 0;
					gPauseButton[i].w = SMALL_BUTTON_WIDTH;
					gPauseButton[i].h = SMALL_BUTTON_HEIGHT;
				}
			}

			if (!gContinueButtonTexture.LoadFromFile("imgs/button/big_button/continue_button.png", gRenderer))
			{
				std::cout << "Failed to load continue_button image " << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gContinueButton[i].x = SMALL_BUTTON_WIDTH * i;
					gContinueButton[i].y = 0;
					gContinueButton[i].w = SMALL_BUTTON_WIDTH;
					gContinueButton[i].h = SMALL_BUTTON_HEIGHT;
				}
			}

			
			if (!gBackgroundTexture.LoadFromFile(LAYER.c_str(), gRenderer))
			{
				std::cout << "Failed to load background image" << std::endl;
				success = false;
			}
			

			if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
			{
				std::cout << "Failed to load ground image" << std::endl;
				success = false;
			}

			if (!gSonicTexture.LoadFromFile("imgs/character/sonic.png", gRenderer))
			{
				std::cout << "Failed to load sonic_run image." << std::endl;
				success = false;
			}
			if (!gShadowTexture.LoadFromFile("imgs/character/shadow.png", gRenderer))
			{
				std::cout << "Failed to load shadow_run image." << std::endl;
				success = false;
			}
			else
			{
				gCharacterClips[0].x = CHARACTER_FRAME_WIDTH * 0;
				gCharacterClips[0].y = 0;
				gCharacterClips[0].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[0].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[1].x = CHARACTER_FRAME_WIDTH * 1;
				gCharacterClips[1].y = 0;
				gCharacterClips[1].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[1].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[2].x = CHARACTER_FRAME_WIDTH * 2;
				gCharacterClips[2].y = 0;
				gCharacterClips[2].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[2].h = CHARACTER_FRAME_HEIGHT;

				gCharacterClips[3].x = CHARACTER_FRAME_WIDTH * 3;
				gCharacterClips[3].y = 0;
				gCharacterClips[3].w = CHARACTER_FRAME_WIDTH;
				gCharacterClips[3].h = CHARACTER_FRAME_HEIGHT;
			}

			if (!gLoseTexture.LoadFromFile("imgs/background/lose.png", gRenderer))
			{
				std::cout << "Failed to load lose image." << std::endl;
				success = false;
			}
			
			if (!gChooseShadowButtonTexture.LoadFromFile("imgs/button/big_button/blackSonic.png", gRenderer))
			{
				std::cout << "Failed to load shadow button image." << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gChooseShadowButton[i].x = CHOOSE_CHARACTER_BUTTON_WIDTH * i;
					gChooseShadowButton[i].y = 0;
					gChooseShadowButton[i].w = CHOOSE_CHARACTER_BUTTON_WIDTH;
					gChooseShadowButton[i].h = CHOOSE_CHARACTER_BUTTON_HEIGHT;
				}
			}

			if (!gChooseSonicButtonTexture.LoadFromFile("imgs/button/big_button/blueSonic.png", gRenderer))
			{
				std::cout << "Failed to load sonic button image." << std::endl;
				success = false;
			}
			else
			{
				for (int i = 0; i < BUTTON_TOTAL; ++i)
				{
					gChooseSonicButton[i].x = CHOOSE_CHARACTER_BUTTON_WIDTH * i;
					gChooseSonicButton[i].y = 0;
					gChooseSonicButton[i].w = CHOOSE_CHARACTER_BUTTON_WIDTH;
					gChooseSonicButton[i].h = CHOOSE_CHARACTER_BUTTON_HEIGHT;
				}
			}

			if (!gChooseCharacterBackGroundTexture.LoadFromFile("imgs/background/characterSelectionBg.png", gRenderer))
			{
				std::cout << "Failed to load choose character background image" << std::endl;
				success = false;
			}
		}
	}
	return success;
}

void Game::Close()
{
	gMenuTexture.Free();
	gInstructionTexture.Free();
	gCharacterTexture.Free();
	gSonicTexture.Free();
	gShadowTexture.Free();	
	gGroundTexture.Free();
	gPlayButtonTexture.Free();
	gHelpButtonTexture.Free();
	gExitButtonTexture.Free();
	gBackButtonTexture.Free();
	gPauseButtonTexture.Free();
	gContinueButtonTexture.Free();
	gLoseTexture.Free();
	gText1Texture.Free();
	gScoreTexture.Free();
	gText2Texture.Free();
	gHighScoreTexture.Free();

	gChooseShadowButtonTexture.Free();
	gChooseSonicButtonTexture.Free();
	gChooseCharacterBackGroundTexture.Free();
	
	gBackgroundTexture.Free();
	

	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gMenuMusic);
	Mix_FreeChunk(gClick);
	Mix_FreeChunk(gLose);
	Mix_FreeChunk(gJump);
	gMusic = nullptr;
	gMenuMusic = nullptr;
	gClick = nullptr;
	gLose = nullptr;
	gJump = nullptr;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	IMG_Quit();
	Mix_Quit();
	SDL_Quit();

	std::cout << "Free everything!" << std::endl;
}