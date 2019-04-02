#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include "tile.h"

class Pacman
{
public:
    static const int PACMAN_WIDTH = 25;
    static const int PACMAN_HEIGHT = 25;
    static const int PACMAN_VEL = 5;

    // Constructor
    Pacman();

    // Handle event
    void handleEvent(SDL_Event& e);

    // Move the dot
    void move(Tile* tiles[], int SCREEN_WIDTH, int SCREEN_HEIGHT);

    // Render the texture representing the dot
    void render();
private:
    // Collision box
    SDL_Rect mBox;

    // Velocity
    int mVelX , mVelY;
};

#endif // PACMAN_H
