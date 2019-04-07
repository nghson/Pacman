#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include "Tile.h"
#include "Texture.h"

//Pacman that will move around on the screen by keystrokes
class Pacman
{
public:
    //Indicators of moving direction
    enum
    {
        MOVING_LEFT,
        MOVING_RIGHT,
        MOVING_DOWN,
        MOVING_UP,
        NOT_MOVING
    };

    //The dimensions of pacman
    static const int PACMAN_WIDTH = 20;
    static const int PACMAN_HEIGHT = 20;

    //Maximum axis velocity of pacman
    static const int PACMAN_VEL = 5;

    //Initializes the variables
    Pacman(int _x, int _y);

    //Takes key presses and adjusts pacman's velocity
    void handleEvent(SDL_Event& e, Tile* tiles[]);

    //Moves pacman and check collision against wall tiles
    void move(Tile *tiles[]);

    //Shows pacman on the screen
    void render(LTexture& gDotTexture, SDL_Renderer* gRenderer);

    //Can pacman move in the given direction? If not, maintain the current direction
    bool canMove(int direction, Tile* tiles[]);

    //Can pacman use eNext to move?
    bool handleNextEvent(Tile* tiles[]);

public:
    //Collision box of the pacman
    SDL_Rect mBox;

    //The velocity of the pacman
    int mVelX, mVelY;

    //Next keystroke, receiving values from the above enumeration
    int eNext;
};

#endif // PACMAN_H