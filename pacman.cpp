#include "pacman.h"

Pacman::Pacman()
{
    mBox.x = 0;
    mBox.y = 0;
    mBox.w = PACMAN_WIDTH;
    mBox.h = PACMAN_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}

void Pacman::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
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
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += PACMAN_VEL;
            break;
        case SDLK_DOWN:
            mVelY -= PACMAN_VEL;
            break;
        case SDLK_LEFT:
            mVelX += PACMAN_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= PACMAN_VEL;
            break;
        }
    }
}

void Pacman::move(Tile* tiles[], int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + PACMAN_WIDTH > SCREEN_WIDTH) || touchesWall(mBox, tiles))
    {
        mBox.x -= mVelX;
    }

    mBox.y += mVelY;
    if ((mBox.y < 0) || (mBox.y + PACMAN_HEIGHT > SCREEN_HEIGHT) || touchesWall(mBox, tiles))
    {
        mBox.y -= mVelY;
    }
}

void Pacman::render()
{
    gPacmanTexture.render(mBox.x, mBox.y);
}
