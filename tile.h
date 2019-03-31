#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

class Tile
{
public:
    // Constructor
    Tile(int x, int y, int tileWidth, tileHeight);

    // Render the wall tile
    void render();

    // Get the tile type
    int getType();

    // Get the collision box
    SDL_Rect getBox();
private:
    // Attributes of the wall tile
    SDL_Rect mBox;

    // The tile type, either 1 (wall) or 0 (space)
    int mType;
};

#endif // TILE_H
