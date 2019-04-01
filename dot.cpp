#include "dot.h"

Dot::Dot()
{
    mPosX = 0;
    mPosY = 0;

    mCollider.w = DOT_WIDTH;
    mCollider.h = DOT_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}

Dot::handleEvent(SDL_Event& e)
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
        swtich (e.key.keysym.sym)
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

void Dot::move()
{
    mPosX += mVelX;
    mCollider.x = mPosX;
    if ((mPosX < 0 || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || touchesWall(mBox, tiles))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || touchesWall(mBox, tiles))
    {
        mPosY -= mVelY;
    }
}

void Dot::render(LTexture& gDotTexture)
{
    gDotTexture.render(mPosX, mPosY);
}
