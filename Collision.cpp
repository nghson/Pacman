#include "Collision.h"

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are inside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are inside B
    return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[], const int TOTAL_TILES)
{
    //Go through the tiles
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        //If the tile is a wall type tile
        if (tiles[i]->getType() == 1)
        {
            //If the collision box touches the wall tile
            if (checkCollision(box, tiles[i]->getBox()))
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

bool canMove(SDL_Rect box, int direction, Tile* tiles[], int vel)
{
    SDL_Rect testBox;
    switch (direction)
    {
        //MOVING_UP
        case 0:
            testBox = {box.x, box.y - vel, box.w, box.h};
            if (touchesWall(testBox, tiles)) return false;
            break;
        //MOVING_DOWN
        case 1:
            testBox = {box.x, box.y + vel, box.w, box.h};
            if (touchesWall(testBox, tiles)) return false;
            break;
        //MOVING_LEFT
        case 2:
            testBox = {box.x - vel, box.y, box.w, box.h};
            if (touchesWall(testBox, tiles)) return false;
            break;
        //MOVING_RIGHT
        case 3:
            testBox = {box.x + vel, box.y, box.w, box.h};
            if (touchesWall(testBox, tiles)) return false;
            break;
        }
    return true;
}
