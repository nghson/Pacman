#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include "texture.h"
#include "tile.h"
#include "main.h"

class Dot
{
public:
    static const int DOT_WIDTH = 25;
    static const int DOT_HEIGHT = 25;
    static const int DOT_VEL = 5;

    // Constructor
    Dot();

    // Handle event
    void handleEvent(SDL_Event& e);

    // Move the dot
    void move(Tile* tiles[]);

    // Render the texture representing the dot
    void render(LTexture& gDotTexture);
private:
    // Collision box
    SDL_Rect mBox;

    // Velocity
    int mVelX , mVelY;
};
#endif // DOT_H
