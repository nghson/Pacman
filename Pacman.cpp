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
	if ((e.type == SDL_KEYDOWN && e.key.repeat == 0))
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY -= PACMAN_VEL; break;
            case SDLK_DOWN: mVelY += PACMAN_VEL; break;
            case SDLK_LEFT: mVelX -= PACMAN_VEL; break;
            case SDLK_RIGHT: mVelX += PACMAN_VEL; break;
        }
    }

    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += PACMAN_VEL; break;
            case SDLK_DOWN: mVelY -= PACMAN_VEL; break;
            case SDLK_LEFT: mVelX += PACMAN_VEL; break;
            case SDLK_RIGHT: mVelX -= PACMAN_VEL; break;
        }
    }
}

bool Pacman::move(Tile *tiles[])
{
    bool deadEnd = false;

    while (true)
    {
        //Move pacman left or right
        mBox.x += mVelX;

        //If pacman went too far to the left or right
        if ((mBox.x < 0) || (mBox.x + PACMAN_WIDTH > LEVEL_WIDTH))
        {
            //move back
            mBox.x -= mVelX;
        }
        //If pacman touched a wall
        else if (touchesWall(mBox, tiles))
        {
            //move back
            mBox.x -= mVelX;
            //Pacman cannot take a turn
            deadEnd = true;
        }
    }

    while (true)
    {
        //Move pacman up or down
        mBox.y += mVelY;

        //If pacman went too far up or down or touched a wall
        if((mBox.y < 0) || (mBox.y + PACMAN_HEIGHT > LEVEL_HEIGHT))
        {
            //move back
            mBox.y -= mVelY;
        }
        // If pacman touched a wall
        else if (touchesWall(mBox, tiles))
        {
            //move back
            mBox.y -= mVelY;
            //Pacman cannot take a turn
            deadEnd = true;
        }
    }

    return deadEnd;
}

void Pacman::render(LTexture& gPacmanTexture, SDL_Renderer* gRenderer)
{
    //Show the dot
	gPacmanTexture.render(mBox.x, mBox.y, gRenderer);
}
