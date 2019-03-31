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

}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}

bool setTiles(Tile* tiles[], std::string path)
{
    bool success = true;
    int x = 0, y = 0;

    std::ifstream Map(path.c_str());

    if (!Map.is_open())
    {
        printf("Error: Unable to load map file!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < TOTAL_TYPES_OF_TILES; i++)
        {
            int tileType;
            Map >> tileType;

            if (Map.fail())
            {
                printf("Error: Unexpected end of file when loading map!\n");
                success = false;
                break;
            }

            if (tileType >= 0) && (tileType < TOTAL_TYPES_OF_TILES)
            {
                tiles[i] = new Tile(x, y, tileType);
            }
            else
            {
                printf("Error: Invalid tile type when loading map at %d!\n", i);
                success = false;
                break;
            }

        }
    }
}
