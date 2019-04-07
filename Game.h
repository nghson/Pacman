#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Texture.h"
#include "Tile.h"
#include "Pacman.h"
#include "CheckCollision.h"

//Screen dimension constants
const int SCREEN_WIDTH = 560;
const int SCREEN_HEIGHT = 620;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Textures
LTexture gPacmanTexture;
LTexture gWallTileTexture;
LTexture gSpaceTileTexture;
LTexture gSmallYummyTexture;
LTexture gBigYummyTexture;

#endif // GAME_H
