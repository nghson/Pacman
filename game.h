#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <string>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <fstream>
#include "texture.h"
#include "tile.h"
#include "pacman.h"
#include "collision.h"

const int SCREEN_WIDTH = 700; // 700 = 28*25
const int SCREEN_HEIGHT = 775; // 775 = 31*25

const int SPACE = 0;
const int WALL = 1;
const int PACMAN = 2;

const int SDLERROR = 1;
const int IMGERROR = 2;
void logError(std::string errorType);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
bool init();

const int TOTAL_TILES = 868; // 868 = 28*31
const int TYPES_OF_TILES = 2;
const int TILE_WIDTH = 25;
const int TILE_HEIGHT = 25;
bool setTiles(Tile* tiles[], std::string path);

bool loadTileMedia(Tile* tiles[], std::string path);

LTexture gWallTexture;
LTexture gPacmanTexture;
LTexture gSpaceTexture;
bool loadTextureMedia(int textureType, std::string path);

void close(Tile* tiles[]);

Pacman pacman;

#endif // GAME_H
