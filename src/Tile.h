#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include "Texture.h"

//The tile
class Tile
{
public:
    //Initializes position and type
    Tile(int x, int y, int tileType);

    //Shows the tile
    void render(Texture& tileTexture, SDL_Renderer* renderer);

    //Get the tile type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

private:
    //Tile constants
    const int TILE_WIDTH = 20;
    const int TILE_HEIGHT = 20;

    //The attributes of the tile
    SDL_Rect box;

    //The tile type
    int type;
};

#endif // TILE_H
