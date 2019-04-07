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

    //Initialize ePending
    ePending = NOT_MOVING;
}

void Pacman::move(Tile *tiles[], int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    //Move pacman left or right
    mBox.x += mVelX;

    //If pacman touched a wall
    if (touchesWall(mBox, tiles))
    {
        //move back
        mBox.x -= mVelX;
    }
    //Handle the teleport
    if (mBox.x < 0)
    {
        mBox.x = SCREEN_WIDTH - PACMAN_WIDTH;
    }
    else if (mBox.x + PACMAN_WIDTH > SCREEN_WIDTH)
    {
        mBox.x = 0;
    }

    //Move pacman up or down
    mBox.y += mVelY;

    //If pacman touched a wall
    if (touchesWall(mBox, tiles))
    {
        //move back
        mBox.y -= mVelY;
    }

    //Debug
    printf("mBox.x: %d mBox.y: %d\n", mBox.x, mBox.y);
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

void Pacman::handleEvent(SDL_Event& e, Tile* tiles[])
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            if (canMove(MOVING_UP, tiles))
            {
                mVelY = -PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            else
            {
                ePending = MOVING_UP;
                return;
            }
            break;
        case SDLK_DOWN:
            if (canMove(MOVING_DOWN, tiles))
            {
                mVelY = PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            else
            {
                ePending = MOVING_DOWN;
                return;
            }
            break;
        case SDLK_LEFT:
            if (canMove(MOVING_LEFT, tiles))
            {
                mVelX = -PACMAN_VEL;
                mVelY = 0;
                ePending = NOT_MOVING;
                return;
            }
            else
            {
                ePending = MOVING_LEFT;
                return;
            }
            break;
        case SDLK_RIGHT:
            if (canMove(MOVING_RIGHT, tiles))
            {
                mVelX = PACMAN_VEL;
                mVelY = 0;
                ePending = NOT_MOVING;
                return;
            }
            else
            {
                ePending = MOVING_RIGHT;
                return;
            }
            break;
        }
    }

    //Debug
    printf("mVelX: %d mVelY: %d\n", mVelX, mVelY);
}

void Pacman::handlePending(Tile* tiles[])
{
    //Debug
    printf("ePending: %d\n", ePending);

    //Check for pending key
    if (ePending != NOT_MOVING)
    {
        switch (ePending)
        {
        case MOVING_UP:
            if (canMove(MOVING_UP, tiles))
            {
                mVelY = -PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_DOWN:
            if (canMove(MOVING_DOWN, tiles))
            {
                mVelY = PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_LEFT:
            if (canMove(MOVING_LEFT, tiles))
            {
                mVelX = -PACMAN_VEL;
                mVelY = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_RIGHT:
            if (canMove(MOVING_RIGHT, tiles))
            {
                mVelX = PACMAN_VEL;
                mVelY = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        }
    }
}
