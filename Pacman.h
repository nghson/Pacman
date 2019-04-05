#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include "Tile.h"
#include "Texture.h"

//Pacman that will move around on the screen by keystrokes
class Pacman
{
public:
    //The dimensions of pacman
    static const int PACMAN_WIDTH = 20;
    static const int PACMAN_HEIGHT = 20;

    //Direction from keystroke
    static const int UP = 0;
    static const int DOWN = 1;
    static const int LEFT = 2;
    static const int RIGHT = 3;

    //Maximum axis velocity of pacman
    static const int PACMAN_VEL = 5;

    //Initializes the variables
    Pacman(int _x, int _y);

    //Takes key presses and adjusts pacman's velocity
    void handleEvent(SDL_Event& e);

    //Moves pacman and check collision against wall tiles
    bool move(Tile *tiles[]);

    //Shows pacman on the screen
    void render(LTexture& gDotTexture, SDL_Renderer* gRenderer);

private:
    //Collision box of the pacman
    SDL_Rect mBox;

    //The velocity of the pacman
    int mVelX, mVelY;
};

#endif // PACMAN_H
