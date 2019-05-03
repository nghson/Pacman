#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "Tile.h"

//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);

//Checks collision box against set of tiles
bool touchesWall(SDL_Rect box, Tile* tiles[], const int TOTAL_TILES = 868);

//Can the object move in the provided direction?
bool canMove(SDL_Rect box, int direction, Tile* tiles[], int vel = 2);

#endif // COLLISION_H
