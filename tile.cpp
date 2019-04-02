#include "tile.h"

Tile::Tile(int x, int y, int tileType)
{
	mBox.x = x;
	mBox.y = y;

	mBox.w = TILE_WIDTH;
	mBox.h = TILE_HEIGHT;

	mType = tileType;
}

void Tile::render(int tileType)
{
    switch (tileType)
    {
    // Space tile
    case SPACE:
        gWallTexture.render(mBox.x, mBox.y);
        break;
    // Wall tile
    case WALL:
        gSpaceTexture.render(mBox.x, mBox.y);
        break;
    // Handle exception
    default:
        printf("Undefined tile type provided!\n");
        break;
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}



