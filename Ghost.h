#ifndef GHOST_H
#define GHOST_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <cfloat>
#include <stdlib.h>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include "Tile.h"
#include "Texture.h"
#include "Yummy.h"

//Saves data about position
class Ghost
{
public:
    //Constructor
    Ghost(int _x, int _y, int _name, int _movingMode);

    //Render ghost on screen
    void render(Texture& spriteSheetTexture, SDL_Rect spriteClips[][4], int frame, SDL_Renderer* renderer);

    //Heuristic: Manhattan distance between a and b
    int heuristic(SDL_Rect a, SDL_Rect b);

    //Move the ghost
    void move(SDL_Rect pacmanPos, Tile* tiles[]);

    //Pathfinder: just moving randomly
    int randomPath(Tile* tiles[]);

    //Pathfinder: A* Search
    std::vector<SDL_Rect> aStarPath(SDL_Rect start, SDL_Rect goal, Tile* tiles[]);

    //Pathfinder: just moving stupidly
    int stupidPath(SDL_Rect goal, Tile* tiles[]);

    //Get current position
    SDL_Rect getPos();

    //Reset position after pacman died
    void resetPos();

private:
    //Initial position
    SDL_Rect initPos;

    //Size of ghost
    const int GHOST_WIDTH = 20;
    const int GHOST_HEIGHT = 20;

    //Velocity of ghost
    const int GHOST_VEL = 2;

    //Indicators of moving direction
    enum
    {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        NOT_MOVING
    };

    //Indicators of ghost moving mode
    enum
    {
        RANDOM,
        CHASE,
        STUPID
    };

    //Indicators of names
    enum
    {
        BLINKY,
        CLYDE,
        INKY,
        PINKY
    };

    //Name
    int name;

    //Ghost moving mode
    int movingMode;

    //Position of ghost
    SDL_Rect pos;

    //Current direction
    int dir;
};

#endif // GHOST_H
