#include "Ghost.h"

Ghost::Ghost(int _x, int _y)
{
    //Initialize position of ghost
    pos = {_x, _y, GHOST_WIDTH, GHOST_HEIGHT};

    //Initialize mode of ghost
    mode = NORMAL;

    //Initialize direction
    dir = NOT_MOVING;
}

//Move the ghost: default
void Ghost::move(SDL_Rect pacmanPos, Tile* tiles[])
{
    int distUp = INT_MAX, distDown = INT_MAX, distLeft = INT_MAX, distRight = INT_MAX;
    if (canMove(pos, GHOST_VEL, MOVING_UP, tiles))
            distUp = manhattanDist(pacmanPos, {pos.x, pos.y-GHOST_VEL, pos.w, pos.h});
    if (canMove(pos, GHOST_VEL, MOVING_DOWN, tiles))
        distDown = manhattanDist(pacmanPos, {pos.x, pos.y+GHOST_VEL, pos.w, pos.h});
    if (canMove(pos, GHOST_VEL, MOVING_LEFT, tiles))
        distLeft = manhattanDist(pacmanPos, {pos.x-GHOST_VEL, pos.y, pos.w, pos.h});
    if (canMove(pos, GHOST_VEL, MOVING_RIGHT, tiles))
        distRight = manhattanDist(pacmanPos, {pos.x+GHOST_VEL, pos.y, pos.w, pos.h});
    int minDist = std::min(std::min(distUp, distDown), std::min(distLeft, distRight));
    if (minDist != INT_MAX)
    {
        if (minDist == distUp)
        {
            pos.y -= GHOST_VEL;
            dir = MOVING_UP;
        }
        else if (minDist == distDown)
        {
            pos.y += GHOST_VEL;
            dir = MOVING_DOWN;
        }
        else if (minDist == distLeft)
        {
            pos.x -= GHOST_VEL;
            dir = MOVING_LEFT;
        }
        else if (minDist == distRight)
        {
            pos.x += GHOST_VEL;
            dir = MOVING_RIGHT;
        }
    }
}

int Ghost::manhattanDist(SDL_Rect a, SDL_Rect b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void Ghost::changeMode()
{
    switch (mode)
    {
    case NORMAL:
        mode = VULNERABLE;
        break;
    case VULNERABLE:
        mode = NORMAL;
        break;
    }
}

int Ghost::getMode()
{
    return mode;
}

void Ghost::render(Texture& spriteSheetTexture, SDL_Rect spriteClips[][4], int frame, SDL_Renderer* renderer)
{
    if (dir == MOVING_LEFT)
    {
        SDL_Rect* currentClip = &spriteClips[0][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_DOWN)
    {
        SDL_Rect* currentClip = &spriteClips[1][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_RIGHT)
    {
        SDL_Rect* currentClip = &spriteClips[2][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_UP)
    {
        SDL_Rect* currentClip = &spriteClips[3][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == NOT_MOVING)
    {
        SDL_Rect* currentClip = &spriteClips[0][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
}

SDL_Rect Ghost::getPos()
{
    return pos;
}
