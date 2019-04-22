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

    //Initialize number of yummy
    mYummy = TOTAL_YUMMY;
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
}

void Pacman::render(Texture& pacmanTexture, SDL_Renderer* renderer)
{
    //Show the pacman
	pacmanTexture.render(mBox.x, mBox.y, renderer);
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
            if (canMove(mBox, PACMAN_VEL, MOVING_UP, tiles))
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
            if (canMove(mBox, PACMAN_VEL, MOVING_DOWN, tiles))
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
            if (canMove(mBox, PACMAN_VEL, MOVING_LEFT, tiles))
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
            if (canMove(mBox, PACMAN_VEL, MOVING_RIGHT, tiles))
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
}

void Pacman::handlePending(Tile* tiles[])
{
    //Check for pending key
    if (ePending != NOT_MOVING)
    {
        switch (ePending)
        {
        case MOVING_UP:
            if (canMove(mBox, PACMAN_VEL, MOVING_UP, tiles))
            {
                mVelY = -PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_DOWN:
            if (canMove(mBox, PACMAN_VEL, MOVING_DOWN, tiles))
            {
                mVelY = PACMAN_VEL;
                mVelX = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_LEFT:
            if (canMove(mBox, PACMAN_VEL, MOVING_LEFT, tiles))
            {
                mVelX = -PACMAN_VEL;
                mVelY = 0;
                ePending = NOT_MOVING;
                return;
            }
            break;
        case MOVING_RIGHT:
            if (canMove(mBox, PACMAN_VEL, MOVING_RIGHT, tiles))
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

std::vector<int> Pacman::eatYummy(Yummy* yummy[])
{
    std::vector<int> eatenYummy;
    //Check if pacman has eaten which yummy
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (checkCollision(mBox, yummy[i]->getBox()))
        {
            eatenYummy.push_back(i);
        }
    }
    //Update the number of yummy left
    mYummy -= eatenYummy.size();

    return eatenYummy;
}

int Pacman::getYummy()
{
    return mYummy;
}

SDL_Rect Pacman::getBox()
{
    return mBox;
}
