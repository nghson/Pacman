#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "CheckCollision.h"
#include "Texture.h"

//The tile
class Tile
{
public:
    //Types of tiles
    static const int SPACE_TILE = 0;
    static const int WALL_TILE = 1;

    //The dimensions of the level
    static const int LEVEL_WIDTH = 560;
    static const int LEVEL_HEIGHT = 620;

    //Tile constants
    static const int TILE_WIDTH = 20;
    static const int TILE_HEIGHT = 20;
    static const int TOTAL_TILES = 868; //868 = 28*31
    static const int TOTAL_TILE_TYPES = 2;

    //Initializes position and type
    Tile(int x, int y, int tileType);

    //Shows the tile
    void render(LTexture& gTileTexture, SDL_Renderer* gRenderer);

    //Get the tile type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

private:
    //The attributes of the tile
    SDL_Rect mBox;

    //The tile type
    int mType;
};

//Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile* tiles[]);

#endif // TILE_H
