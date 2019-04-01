#include "dot.h"

Dot::Dot()
{
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = DOT_WIDTH;
    mBox.h = DOT_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY += DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += DOT_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= DOT_VEL;
            break;
        case SDLK_LEFT:
            mVelX += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= DOT_VEL;
            break;
        }
    }
}

void Dot::move(Tile* tiles[])
{
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + DOT_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
    }

    mBox.y += mVelY;
    if ((mBox.y < 0) || (mBox.y + DOT_HEIGHT > SCREEN_HEIGHT) || touchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
    }
}

void Dot::render()
{
    gPacmanTexture.render(mBox.x, mBox.y);
}
