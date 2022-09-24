#include "Tile.h"

Tile::Tile(int x, int y, int tileType)
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;
}

void Tile::render(Texture& tileTexture, SDL_Renderer* renderer)
{
    tileTexture.render(box.x, box.y, renderer);
}

int Tile::getType()
{
    return type;
}

SDL_Rect Tile::getBox()
{
    return box;
}
