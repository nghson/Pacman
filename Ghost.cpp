#include "Ghost.h"

Ghost::Ghost(int _x, int _y)
{
    //Initialize position of ghost
    pos = {_x, _y, GHOST_WIDTH, GHOST_HEIGHT};

    //Initialize mode of ghost
    mode = NORMAL;
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
        if (minDist == distUp) pos.y -= GHOST_VEL;
        else if (minDist == distDown) pos.y += GHOST_VEL;
        else if (minDist == distLeft) pos.x -= GHOST_VEL;
        else if (minDist == distRight) pos.x += GHOST_VEL;
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

void Ghost::render(Texture& ghostTexture, SDL_Renderer* renderer)
{
    ghostTexture.render(pos.x, pos.y, renderer);
}

SDL_Rect Ghost::getPos()
{
    return pos;
}
