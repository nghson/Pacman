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
