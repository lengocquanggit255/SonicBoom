#ifndef POWERUP_H_
#define POWERUP_H_

#include "LTexture.h"

#define POWER_UP_MAX_HEIGHT 200
#define POWER_UP_MIN_HEIGHT 300

#define POWER_UP_POSITION_RANGE 250

class PowerUp
{
public:
	PowerUp();
	
	~PowerUp();

	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetSpeed(const int& acceleration);

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();

	bool isGenerated = false;
	
	Uint32 powerUpTimer = 0;
	Uint32 currentTime = 0;
private:
	int posX, posY;

	int eWidth, eHeight;

	SDL_Texture *PowerUpTexture;
};

#endif // !ENEMY_H_