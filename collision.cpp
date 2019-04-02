#include "collision.h"

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x, leftB = b.x;
    int rightA = a.x + a.w, rightB = b.x + b.w;
    int topA = a.y, topB = b.y;
    int bottomA = a.y + a.h, bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }

    if(topA >= bottomB)
    {
        return false;
    }

    if(rightA <= leftB)
    {
        return false;
    }

    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (tiles[i]->getType() == WALL)
        {
            if (checkCollision(box, tiles[i]->getBox()))
            {
                return true;
            }
        }
    }
    return false;
}
