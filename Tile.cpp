#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
    //Get the offsets
    mBox.x = x;
    mBox.y = y;

    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;

    //Get the tile type
    mType = tileType;
}

void Tile::render(Texture& tileTexture, SDL_Renderer* renderer)
{
    tileTexture.render(mBox.x, mBox.y, renderer);
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
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

bool canMove(SDL_Rect box, int vel, int direction, Tile* tiles[])
{
    switch (direction)
    {
        case MOVING_LEFT:
            box.x -= vel;
            if (touchesWall(box, tiles))
            {
                //move back
                box.x += vel;
                return false;
            }
            box.x += vel;
            break;
        case MOVING_RIGHT:
            box.x += vel;
            if (touchesWall(box, tiles))
            {
                //move back
                box.x -= vel;
                return false;
            }
            box.x -= vel;
            break;
        case MOVING_UP:
            box.y -= vel;
            if (touchesWall(box, tiles))
            {
                //move back
                box.y += vel;
                return false;
            }
            box.y += vel;
            break;
        case MOVING_DOWN:
            box.y += vel;
            if (touchesWall(box, tiles))
            {
                //move back
                box.y -= vel;
                return false;
            }
            box.y -= vel;
            break;
        }
    return true;
}

