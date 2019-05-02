#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
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

//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

//Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile* tiles[], const int TOTAL_TILES = 868);

//Can the object move in the provided direction?
bool canMove(SDL_Rect box, int direction, Tile* tiles[], int vel = 2);

#endif // TILE_H
