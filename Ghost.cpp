#include "Ghost.h"

Ghost::Ghost(int _x, int _y)
{
    //Initialize the collision box
    mBox.x = _x;
    mBox.y = _y;
	mBox.w = GHOST_WIDTH;
	mBox.h = GHOST_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    //Initialize number of yummy
    mYummy = TOTAL_YUMMY;
}

void Ghost::move(Tile *tiles[], int movingMode)
{

}

SDL_Rect Ghost::getBox()
{
    return mBox;
}

void Ghost::render(Texture& ghostTexture, SDL_Renderer* renderer)
{
    //Show the pacman
	ghostTexture.render(mBox.x, mBox.y, renderer);
}

bool Ghost::canMove(int direction, Tile* tiles[])
{
    switch (direction)
    {
        case MOVING_LEFT:
            mBox.x -= GHOST_VEL;
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.x += GHOST_VEL;
                return false;
            }
            mBox.x += GHOST_VEL;
            break;
        case MOVING_RIGHT:
            mBox.x += GHOST_VEL;
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.x -= GHOST_VEL;
                return false;
            }
            mBox.x -= GHOST_VEL;
            break;
        case MOVING_UP:
            mBox.y -= GHOST_VEL;
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.y += GHOST_VEL;
                return false;
            }
            mBox.y += GHOST_VEL;
            break;
        case MOVING_DOWN:
            mBox.y += GHOST_VEL;
            if (touchesWall(mBox, tiles))
            {
                //move back
                mBox.y -= GHOST_VEL;
                return false;
            }
            mBox.y -= GHOST_VEL;
            break;
        }
    return true;
}

