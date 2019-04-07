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

    //Initialize eNext
    eNext = NOT_MOVING;
}

void Pacman::handleEvent(SDL_Event& e, Tile* tiles[])
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch(e.key.keysym.sym)
        {
        case SDLK_UP:
            if (canMove(MOVING_UP, tiles))
            {
                mVelY = -PACMAN_VEL;
                mVelX = 0;
            }
            else
            {
                eNext = MOVING_UP;
            }
            break;
        case SDLK_DOWN:
            if (canMove(MOVING_DOWN, tiles))
            {
                mVelY = PACMAN_VEL;
                mVelX = 0;
            }
            else
            {
                eNext = MOVING_DOWN;
            }
            break;
        case SDLK_LEFT:
            if (canMove(MOVING_LEFT, tiles))
            {
                mVelX = -PACMAN_VEL;
                mVelY = 0;
            }
            else
            {
                eNext = MOVING_LEFT;
            }
            break;
        case SDLK_RIGHT:
            if (canMove(MOVING_RIGHT, tiles))
            {
                mVelX = PACMAN_VEL;
                mVelY = 0;
            }
            else
            {
                eNext = MOVING_RIGHT;
            }
            break;
        default:
            break;
        }
    }

    //Debug
    printf("mVelX: %d mVelY: %d\n", mVelX, mVelY);
}

void Pacman::move(Tile *tiles[])
{
    //Move the dot left or right
    mBox.x += mVelX;

    //If the dot went too far to the left or right or touched a wall
    if (touchesWall(mBox, tiles))
    {
        //move back
        mBox.x -= mVelX;
    }

    //Move the dot up or down
    mBox.y += mVelY;

    //If the dot went too far up or down or touched a wall
    if (touchesWall(mBox, tiles))
    {
        //move back
        mBox.y -= mVelY;
    }

//    //Debug
//    printf("mBox.x: %d mBox.y: %d\n", mBox.x, mBox.y);
}

void Pacman::render(LTexture& gPacmanTexture, SDL_Renderer* gRenderer)
{
    //Show the dot
	gPacmanTexture.render(mBox.x, mBox.y, gRenderer);
}


bool Pacman::canMove(int direction, Tile* tiles[])
{
    switch (direction)
    {
        case MOVING_LEFT:
            mBox.x -= PACMAN_VEL;
            //If _pacman touches a wall
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.x += PACMAN_VEL;
                return false;
            }
            mBox.x += PACMAN_VEL;
            break;
        case MOVING_RIGHT:
            mBox.x += PACMAN_VEL;
            //If _pacman touches a wall
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.x -= PACMAN_VEL;
                return false;
            }
            mBox.x -= PACMAN_VEL;
            break;
        case MOVING_UP:
            mBox.y -= PACMAN_VEL;
            //If _pacman touches a wall
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.y += PACMAN_VEL;
                return false;
            }
            mBox.y += PACMAN_VEL;
            break;
        case MOVING_DOWN:
            mBox.y += PACMAN_VEL;
            //If _pacman touches a wall
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.y -= PACMAN_VEL;
                return false;
            }
            mBox.y -= PACMAN_VEL;
            break;
        }
    return true;
}

bool Pacman::handleNextEvent(Tile* tiles[])
{
    printf("eNext: %d \n", eNext);
    if (eNext != NOT_MOVING)
    {
        switch (eNext)
        {
            case MOVING_UP:
                if (canMove(MOVING_UP, tiles))
                {
                    mVelY = -PACMAN_VEL;
                    mVelX = 0;
                    return true;
                }
            case MOVING_DOWN:
                if (canMove(MOVING_DOWN, tiles))
                {
                    mVelY = PACMAN_VEL;
                    mVelX = 0;
                    return true;
                }
            case MOVING_LEFT:
                if (canMove(MOVING_LEFT, tiles))
                {
                    mVelX = -PACMAN_VEL;
                    mVelY = 0;
                    return true;
                }
            case MOVING_RIGHT:
                if (canMove(MOVING_RIGHT, tiles))
                {
                    mVelX = PACMAN_VEL;
                    mVelY = 0;
                    return true;
                }
        }
    }
    return false;
}
