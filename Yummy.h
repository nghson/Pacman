#ifndef YUMMY_H
#define YUMMY_H

#include <SDL2/SDL.h>
#include <climits>
#include "CheckCollision.h"
#include "Texture.h"

//Size of yummy
const int SMALL_YUMMY_WIDTH = 4;
const int SMALL_YUMMY_HEIGHT = 4;
const int BIG_YUMMY_WIDTH = 8;
const int BIG_YUMMY_HEIGHT = 8;

//Types of yummy
const int SMALL_YUMMY = 0;
const int NO_YUMMY = 1;
const int BIG_YUMMY = 2;

//Undefined position and size of yummy (along with NO_YUMMY)
const int UNDEFINED_X = INT_MIN;
const int UNDEFINED_Y = INT_MIN;
const int UNDEFINED_W = 0;
const int UNDEFINED_H = 0;

//Number of yummy = number of space tiles
const int TOTAL_YUMMY = 360;

//The yummy
class Yummy
{
public:
    /*
    There are 4 big yummy
    Their position relative to the space and wall tiles:
    tiles[161], tiles[176], tiles[566], tiles[581]
    The rests are small yummy
    */

    //Initialize yummy
    Yummy(int _x, int _y, int _mType);

    //Shows the yummy
    void render(LTexture& gTileTexture, SDL_Renderer* gRenderer);

    //Get the yummy type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

    //Delete yummy as pacman has already eaten them
    void deleteYummy();

private:
    //The attributes of the yummy
    SDL_Rect mBox;

    //The yummy type
    int mType;
};

#endif // YUMMY_H
