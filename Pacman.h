#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <vector>
#include "Tile.h"
#include "Texture.h"
#include "Yummy.h"
#include "CheckCollision.h"

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
    static const int PACMAN_VEL = 2;

    //Initializes the variables
    Pacman(int _x, int _y);

    //Takes key presses and adjusts pacman's velocity
    void handleEvent(SDL_Event& e, Tile* tiles[]);

    //Moves pacman and check collision against wall tiles
    void move(Tile *tiles[], int SCREEN_WIDTH, int SCREEN_HEIGHT);

    //Shows pacman on the screen
    void render(Texture& pacmanTexture, SDL_Renderer* renderer);

    //Handle the pending event
    void handlePending(Tile* tiles[]);

    //Get the number of yummy left
    int getYummy();

    //Pacman eats some yummy!
    std::vector<int> eatYummy(Yummy* yummy[]);

    //Get box
    SDL_Rect getBox();

private:
    //Collision box of the pacman
    SDL_Rect mBox;

    //The velocity of the pacman
    int mVelX, mVelY;

    //Pending keystroke, receiving values from the above enumeration
    int ePending;

    //Number of yummy left
    int mYummy;
};

#endif // PACMAN_H
