#include "Character.h"

Character::Character()//default is character running
{
	posX = SCREEN_WIDTH - 700;
	posY = GROUND;

	status = 0;
}

bool Character::OnGround()
{
	return posY == GROUND;
}

void Character::HandleEvent(SDL_Event& e, Mix_Chunk *gJump)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
            case SDLK_UP:
            {
                if (OnGround())
                {
                    Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                    status = JUMP;
                    jumpCount = 1;           // Reset the jump counter to 1 when the player performs their first jump
                    canDoubleJump = true;    // Allow the player to perform a double jump
                }
                else if (canDoubleJump && jumpCount < 2)
                {
                    Mix_PlayChannel(MIX_CHANNEL, gJump, NOT_REPEATITIVE);
                    status = JUMP;
                    jumpCount++;            // Increment the jump counter when the player performs a double jump
                    canDoubleJump = false;   // Prevent the player from performing another double jump until they land
                }
                break;
            }
            default:
                break;
        }
    }
}

//When the player reaches the maximum height of their jump, change the player's status to FALL so that they start falling
//When the player lands on the ground, Reset the jump counter and allow the player to perform another double jump
void Character::Move()
{
    if (status == JUMP && posY >= MAX_HEIGHT)
    {
        posY -= JUMP_SPEED;
    }
    else if (status == JUMP && posY < MAX_HEIGHT)  // When the player reaches the maximum height of their jump
    {
        status = FALL;      // Change the player's status to FALL so that they start falling
    }
    else if (status == FALL && posY < GROUND)
    {
        posY += FALL_SPEED;
    }
    else if (OnGround())    // When the player lands on the ground
    {
        jumpCount = 0;          // Reset the jump counter
        canDoubleJump = true;   // Allow the player to perform another double jump
    }
}

//Render nhân vật 
void Character::Render(SDL_Rect* currentClip, SDL_Renderer *gRenderer, LTexture gCharacterTexture)
{
	gCharacterTexture.Render(posX, posY, gRenderer, currentClip);
}

int Character::GetPosX()
{
	return posX;
}

int Character::GetPosY()
{
	return posY;
}