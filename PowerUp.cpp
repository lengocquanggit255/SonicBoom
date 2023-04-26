#include "PowerUp.h"

PowerUp::PowerUp()
{
	posX = 0;
	posY = 0;

	eWidth = 0;
	eHeight = 0;

    posX = rand() % (SCREEN_WIDTH + POWER_UP_POSITION_RANGE) + SCREEN_WIDTH;
	posY = rand() % (POWER_UP_MAX_HEIGHT - POWER_UP_MIN_HEIGHT + 1) + POWER_UP_MIN_HEIGHT;

	PowerUpTexture = nullptr;
}

PowerUp::~PowerUp()
{
	posX = -100;
	posY = -100;

	eWidth = 0;
	eHeight = 0;

	isGenerated = false;

	if (PowerUpTexture != nullptr)
	{
		PowerUpTexture = nullptr;
	}
}

void PowerUp:: LoadFromFile(std::string path, SDL_Renderer* gRenderer)
{
    SDL_Texture* tmpTexture = nullptr;

	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if (tmpSurface == nullptr)
	{
		LogError("Can not load image.", IMG_ERROR);
	}
	else
	{
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));

		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr)
		{
			LogError("Can not create texture from surface.", SDL_ERROR);
		}
		else
		{
			eWidth = tmpSurface->w;
			eHeight = tmpSurface->h;
		}

		SDL_FreeSurface(tmpSurface);
	}

	PowerUpTexture = tmpTexture;
}

void PowerUp::Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	SDL_Rect renderSpace = { posX, posY, eWidth, eHeight };
	if (currentClip != nullptr)
	{
		renderSpace.w = currentClip->w;
		renderSpace.h = currentClip->h;
	}
	SDL_RenderCopy(gRenderer, PowerUpTexture, currentClip, &renderSpace);
}


void PowerUp:: Move(const int& acceleration)
{
    posX -= (ENEMY_SPEED + acceleration + 1.5);
    posY = 150 * sin(fmod(posX, SCREEN_WIDTH + POWER_UP_POSITION_RANGE) / 150) + 150;
    if (posX + MAX_ENEMY_WIDTH < 0)
	{
		posX = rand() % (SCREEN_WIDTH + POWER_UP_POSITION_RANGE) + SCREEN_WIDTH;
        posY = rand() % (POWER_UP_MAX_HEIGHT - POWER_UP_MIN_HEIGHT + 1) + POWER_UP_MIN_HEIGHT;
	}
}

int PowerUp::GetSpeed(const int &acceleration)
{
	return POWER_UP_SPEED + acceleration;
}

int PowerUp::GetPosX()
{
	return posX;
}

int PowerUp::GetPosY()
{
	return posY;
}

int PowerUp::GetWidth()
{
	return eWidth;
}