#ifndef YUMMY_H
#define YUMMY_H

#include <SDL2/SDL.h>
#include "Tile.h"
#include "Texture.h"

//The yummy
class Yummy
{
public:
    /*
    There are 4 big yummy
    Their position relative to the space and wall tiles: tiles[146], tiles[161], tiles[566], tiles[581]
    The rests are small yummy
    */

    //Initialize yummy
    Yummy(int _x, int _y, int _type);

    //Shows the yummy
    void render(Texture& yummyTexture, SDL_Renderer* renderer);

    //Get the yummy type
    int getType();

    //Get the collision box
    SDL_Rect getBox();

    //Delete yummy as pacman has already eaten them
    void deleteYummy();

private:
    //Size of yummy
    const int SMALL_YUMMY_WIDTH = 10;
    const int SMALL_YUMMY_HEIGHT = 10;
    const int BIG_YUMMY_WIDTH = 20;
    const int BIG_YUMMY_HEIGHT = 20;

    //Types of yummy
    enum
    {
        SMALL_YUMMY,
        NO_YUMMY,
        BIG_YUMMY
    };

    //The attributes of the yummy
    SDL_Rect box;

    //The yummy type
    int type;
};

#endif // YUMMY_H
