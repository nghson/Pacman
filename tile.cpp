#include "tile.h"

Tile::Tile(int x, int y, int tileType)
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = tileWidth;
	mBox.h = tileHeight;

	mType = tileType;
}

void Tile::render(int x, int y)
{
    gTileTexture.render(x, y);
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

