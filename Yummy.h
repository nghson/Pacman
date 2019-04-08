#ifndef YUMMY_H
#define YUMMY_H

#include <SDL2/SDL.h>
#include "CheckCollision.h"
#include "Texture.h"

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

    //Types of yummy
    static const int SMALL_YUMMY = 0;
    static const int BIG_YUMMY = 1;

    //Size of yummy
    static const int SMALL_YUMMY_WIDTH = 4;
    static const int SMALL_YUMMY_HEIGHT = 4;
    static const int BIG_YUMMY_WIDTH = 8;
    static const int BIG_YUMMY_HEIGHT = 8;

    //Number of yummy
    static const int TOTAL_YUMMY = 360 // = number of space tiles

    //Initialize yummy
    Yummy(int x, int y, int yummyType)

    //Shows the yummy
    void render(LTexture& gTileTexture, SDL_Renderer* gRenderer);

    //Get the yummy type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

private:
    //The attributes of the yummy
    SDL_Rect mBox;

    //The yummy type
    int mType;
};

#endif // YUMMY_H
