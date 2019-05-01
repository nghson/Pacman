#ifndef PACMAN_H
#define PACMAN_H

#include <SDL2/SDL.h>
#include <vector>
#include "Tile.h"
#include "Texture.h"
#include "Yummy.h"
#include "Ghost.h"

//Pacman that will move around on the screen by keystrokes
class Pacman
{
public:
    //Initializes the variables
    Pacman(int _x, int _y, int TOTAL_YUMMY);

    //Takes key presses and adjusts pacman's velocity
    void handleEvent(SDL_Event& e, Tile* tiles[]);

    //Moves pacman and check collision against wall tiles
    void move(Tile *tiles[], int PLAYSCREEN_WIDTH);

    //Shows pacman on the screen
    void render(Texture& spriteSheetTexture, SDL_Rect spriteClips[][4], int frame, SDL_Renderer* renderer);

    //Handle the pending event
    void handlePending(Tile* tiles[]);

    //Has pacman won?
    bool win();

    //Has pacman lost?
    bool lose(Ghost ghost);

    //Pacman eats some yummy!
    std::vector<int> eatYummy(Yummy* yummy[]);

    //Get position box
    SDL_Rect getPos();

    //Get score
    int getScore();

private:
    //Indicators of moving direction
    enum
    {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        NOT_MOVING
    };

    //The dimensions of pacman
    static const int PACMAN_WIDTH = 20;
    static const int PACMAN_HEIGHT = 20;

    //Maximum axis velocity of pacman
    static const int PACMAN_VEL = 2;

    //Position of pacman
    SDL_Rect pos;

    //The velocity of the pacman
    int velX, velY;

    //Pending keystroke, receiving values from the above enumeration
    int ePending;

    //Number of yummy left
    int yummyLeft;

    //Current direction
    int dir;

    //Current score: small = 10, big = 100
    int score;

};

#endif // PACMAN_H
