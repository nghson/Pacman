#ifndef COLLISION_H
#define COLLISION_H

#include <SDL2/SDL.h>
#include "tile.h"
#include "game.h"

bool checkCollision(SDL_Rect a, SDL_Rect b);
bool touchesWall(SDL_Rect box, Tile* tiles[]);

#endif // COLLISION_H
