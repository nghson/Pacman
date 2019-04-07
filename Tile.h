#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "CheckCollision.h"
#include "Texture.h"

//The dimensions of the level
const int LEVEL_WIDTH = 560;
const int LEVEL_HEIGHT = 620;

//Tile constants
const int TILE_WIDTH = 20;
const int TILE_HEIGHT = 20;
const int TOTAL_TILES = 868; //868 = 28*31
const int TOTAL_TILE_TYPES = 2;

//The tile
class Tile
{
    public:
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
