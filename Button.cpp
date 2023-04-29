#include "Button.h"

Button::Button()
{
	position.x = 0;
	position.y = 0;

	currentSprite = BUTTON_MOUSE_OUT;
}

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

	currentSprite = BUTTON_MOUSE_OUT;
}

void Button::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

bool Button::IsInside(int size)// input is the event and size of the button
{
		int x, y;
		int button_width, button_height;
		if (size == PAUSE_AND_CONTINUE_BUTTON)// if small button set width and height
		{
			button_width = PAUSE_AND_CONTINUE_BUTTON_WIDTH;
			button_height = PAUSE_AND_CONTINUE_BUTTON_HEIGHT;
		}
		else if(size == PLAY_BUTON)// if big button set width and height (in menu)
		{
			button_width = PLAY_BUTON_WIDTH;
			button_height = PLAY_BUTON_HEIGHT;
		}
		else if (size == HELP_BUTTON)
		{
			button_width = HELP_BUTTON_WIDTH;
			button_height = HELP_BUTTON_HEIGHT;
		}
		else if (size == EXIT_BUTTON)
		{
			button_width = EXIT_BUTTON_WIDTH;
			button_height = EXIT_BUTTON_HEIGHT;
		}else if(size == OPTION_BUTTON)
		{
			button_width = OPTION_BUTTON_WIDTH;
			button_height = OPTION_BUTTON_HEIGHT;
		}
		else if(size == BACK_BUTTON)
		{
			button_width = BACK_BUTTON_WIDTH;
			button_height = BACK_BUTTON_HEIGHT;
		}else if(size == CHOOSE_CHARACTER_BUTTON)
		{
			button_width = CHOOSE_CHARACTER_BUTTON_WIDTH;
			button_height = CHOOSE_CHARACTER_BUTTON_HEIGHT;
		}else if(size == HARD_MODE_BUTTON)
		{
			button_width = HARD_MODE_BUTTON_WIDTH;
			button_height = HARD_MODE_BUTTON_HEIGHT;
		}else if(size == EASY_MODE_BUTTON)
		{
			button_width = EASY_MODE_BUTTON_WIDTH;
			button_height = EASY_MODE_BUTTON_HEIGHT;
		}else if(size == EXIT_OPTION_BUTTON)
		{
			button_width = EXIT_OPTION_BUTTON_WIDTH;
			button_height = EXIT_OPTION_BUTTON_HEIGHT;
		}

		SDL_GetMouseState(&x, &y);// Get current mouse position

		bool inside = true;// check if the mouse is inside
		if (x < position.x)
		{
			inside = false;
		}
		else if (x > position.x + button_width)
		{
			inside = false;
		}
		else if (y < position.y)
		{
			inside = false;
		}
		else if (y > position.y + button_height)
		{
			inside = false;
		}
		return inside;
	return false;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, LTexture gButtonTexture)
{
	gButtonTexture.Render(position.x, position.y, gRenderer, currentClip);
}