#ifndef BUTTON_H_
#define BUTTON_H_

#include "Game_Base.h"
#include "LTexture.h"

enum ButtonSprite
{
	BUTTON_MOUSE_OUT = 0,// ra ngoài
	BUTTON_MOUSE_OVER = 1,// ben trong
	BUTTON_TOTAL = 2
};

class Button
{
public:
	ButtonSprite currentSprite;

	Button();

	Button(int x, int y);

	void SetPosition(int x, int y);

	bool IsInside(SDL_Event *e, int size);

	void Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture);

private:
	SDL_Point position;
};

#endif // !BUTTON_H_