#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>

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
    void move(SDL_Rect& wall);

    // Render the texture representing the dot
    void render(LTexture& gDotTexture);
private:
    // Position of the dot
    int mPosX, mPosY;

    // Velocity of the dot
    int mVelX, mVelY;

    // Collision box
    SDL_Rect mCollider;
};
#endif // DOT_H
