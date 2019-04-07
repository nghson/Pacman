#ifndef YUMMY_H
#define YUMMY_H

#include "Texture.h"

class Yummy
{
public:
    static const int SMALL_YUMMY = 0;
    static const int BIG_YUMMY = 1;

    Yummy(int x, int y);

private:
    // Yummy type
    int yummyType;

    SDL_Rect box;
};

#endif // YUMMY_H
