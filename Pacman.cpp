#include "Pacman.h"

Pacman::Pacman(int _x, int _y)
{
    //Initialize the collision box
    mBox.x = _x;
    mBox.y = _y;
	mBox.w = PACMAN_WIDTH;
	mBox.h = PACMAN_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Pacman::handleEvent(SDL_Event& e)
{
    //If a key was pressed
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= PACMAN_VEL;
            break;
        case SDLK_DOWN:
            mVelY += PACMAN_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= PACMAN_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += PACMAN_VEL;
            break;
        }
    }
}

void Pacman::move(Tile *tiles[])
{
    //While pacman has not collided with a wall in x-direction
    do
    {
        //Move pacman left or right
        mBox.x += mVelX;
    } while (!touchesWall(mBox, tiles));

    //Pacman has collided with a wall in x-direction, so move back
    mBox.x -= mVelX;

    //While pacman has not collided with a wall in y-direction
    do
    {
        //Move pacman left or right
        mBox.y += mVelY;
    } while (!touchesWall(mBox, tiles));

    //Pacman has collided with a wall in y-direction, so move back
    mBox.y -= mVelY;
}

void Pacman::render(LTexture& gPacmanTexture, SDL_Renderer* gRenderer)
{
    //Show the dot
	gPacmanTexture.render(mBox.x, mBox.y, gRenderer);
}
