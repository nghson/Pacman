#ifndef GHOST_H
#define GHOST_H

#include <SDL2/SDL.h>
#include <vector>
#include "Tile.h"
#include "Texture.h"
#include "Yummy.h"
#include "CheckCollision.h"

//Ghost on control
class Ghost
{
public:
    //The dimensions of pacman
    static const int GHOST_WIDTH = 20;
    static const int GHOST_HEIGHT = 20;

    //Maximum axis velocity of pacman
    static const int GHOST_VEL = 2;

    //Initializes the variables
    Ghost(int _x, int _y);

    //Moves pacman and check collision against wall tiles
    void move(Tile *tiles[], int SCREEN_WIDTH, int SCREEN_HEIGHT, int mode);

    //Shows pacman on the screen
    void render(Texture& ghostTexture, SDL_Renderer* renderer);

    //Can pacman move in the given direction? If not, maintain the current direction
    bool canMove(int direction, Tile* tiles[]);

    //Handle the pending event
    void handlePending(Tile* tiles[]);

    //Get box
    SDL_Rect getBox();

private:
    //Indicators of moving direction
    enum
    {
        MOVING_LEFT,
        MOVING_RIGHT,
        MOVING_DOWN,
        MOVING_UP,
        NOT_MOVING
    };

    //Moving modes: mode 1 is moving randomly, mode 2 is moving using A*
    int movingMode;

    //Collision box of the pacman
    SDL_Rect mBox;

    //The velocity of the pacman
    int mVelX, mVelY;

    //Pending keystroke, receiving values from the above enumeration
    int ePending;

    //Number of yummy left
    int mYummy;
};

#endif // GHOST_H
