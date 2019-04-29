#ifndef GHOST_H
#define GHOST_H

#include <SDL2/SDL.h>
#include <vector>
#include <cmath>
#include <climits>
#include "Tile.h"
#include "Texture.h"
#include "Yummy.h"

//Ghost on control
class Ghost
{
public:
    //Constructor
    Ghost(int _x, int _y);

    //Render ghost on screen
    void render(Texture& ghostTexture, SDL_Renderer* renderer);

    //Move the ghost: default
    void move(SDL_Rect pacmanPos, Tile* tiles[]);

    //Manhattan distance between a and b
    int manhattanDist(SDL_Rect a, SDL_Rect b);

    //Move the ghost: UCS

    //Move the ghost: A*

    //Change ghost mode
    void changeMode();

    //Get current mode
    int getMode();

    //Get current position
    SDL_Rect getPos();

private:
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

    //Position of ghost
    SDL_Rect pos;

    //Indicators of ghost modes
    enum
    {
        NORMAL,
        VULNERABLE
    };

    //Mode of the ghost: vulnerable or normal
    int mode;
};

#endif // GHOST_H
