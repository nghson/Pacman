#include "Yummy.h"

Yummy::Yummy(int x, int y, int yummyType)
{
    //Set the position
    mBox.x = x;
    mBox.y = y;

    //Get the yummy type
    mType = yummyType;

    switch (mType)
    {
    case SMALL_YUMMY:
        mBox.w = SMALL_YUMMY_WIDTH;
        mBox.h = SMALL_YUMMY_HEIGHT;
        break;
    case BIG_YUMMY:
        mBox.w = BIG_YUMMY_WIDTH;
        mBox.h = BIG_YUMMY_HEIGHT;
        break;
    }
}

void Yummy::render(LTexture& gTileTexture, SDL_Renderer* gRenderer)
{
    switch (mType)
    {
    case SMALL_YUMMY:
        gSmallYummyTexture.render(mBox.x, mBox.y, gRenderer);
        break;
    case BIG_YUMMY:BIG_YUMMY:
        gBigYummyTexture.render(mBox.x, mBox.y, gRenderer);
        break;
    }
}

int Yummy::getType()
{
    return mType;
}

SDL_Rect Yummy::getBox()
{
    return mBox;
}

//Delete the eaten yummy
void yummyEaten(Yummy* yummy[])
{
    delete
}
