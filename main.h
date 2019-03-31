#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

const int SCREEN_HEIGHT = 1280;
const int SCREEN_WIDTH = 720;

const int TOTAL_TYPES_OF_TILES = 2;


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gWallTileTexture = NULL;

void logError(std::string errorType);
bool init();
bool loadMedia();
bool setTiles(Tile* tiles[], std::string path);
void close();

#include "texture.h"

LTexture gTileTexture;


