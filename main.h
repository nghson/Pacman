#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "texture.h"
#include "tile.h"
#include "dot.h"

const int SCREEN_HEIGHT = 1280;
const int SCREEN_WIDTH = 720;

const int TOTAL_TILES = 868;  // 868 = 28*31
const int TYPES_OF_TILES = 2;
const int TILE_WIDTH = 25;
const int TILE_HEIGHT = 25;
const int LEVEL_WIDTH = 775;
const int LEVEL_HEIGHT = 700;

const int TILE_SPACE = 0;
const int TILE_WALL = 1;

const int PACMAN = 0;
const int BLINKY = 1;
const int CLYDE = 2;
const int INKEY = 3;
const int PINKY = 4;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void logError(std::string errorType);
bool init();
bool loadTextureMedia(LTexture& gTexture, std::string path);
bool loadTileMedia(Tile* tiles[], std::string path);
void close(Tile* tiles[]);
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool setTiles(Tile* tiles[], std::string path);
bool touchesWall(SDL_Rect box, Tile* tiles[]);

LTexture gWallTexture;
LTexture gPacmanTexture;
LTexture gBlinkyTexture;
LTexture gClydeTexture;
LTexture gInkeyTexture;
LTexture gPinkyTexture;
LTexture gBigYummyTexture;
LTexture gSmallYummyTexture;
LTexture gCherryTexture;
LTexture gSpaceTexture;

Dot gPacmanDot;
Dot gBlinkyDot;
Dot gClydeDot;
Dot gInkeyDot;
Dot gPinkyDot;

#endif // MAIN_H


