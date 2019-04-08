#include "Yummy.h"

Yummy::Yummy(int _x, int _y, int _mType)
{
    //Get the yummy type
    mType = _mType;

    //Set the positions and sizes of yummy
    switch (mType)
    {
    case SMALL_YUMMY:
        mBox.x = _x;
        mBox.y = _y;
        mBox.w = SMALL_YUMMY_WIDTH;
        mBox.h = SMALL_YUMMY_HEIGHT;
        break;
    case BIG_YUMMY:
        mBox.x = _x;
        mBox.y = _y;
        mBox.w = BIG_YUMMY_WIDTH;
        mBox.h = BIG_YUMMY_HEIGHT;
        break;
    case NO_YUMMY:
        mBox.x = UNDEFINED_X;
        mBox.y = UNDEFINED_Y;
        mBox.w = UNDEFINED_W;
        mBox.h = UNDEFINED_H;
        break;
    }
}

void Yummy::render(LTexture& gTileTexture, SDL_Renderer* gRenderer)
{
    gTileTexture.render(mBox.x, mBox.y, gRenderer);

}

int Yummy::getType()
{
    return mType;
}

SDL_Rect Yummy::getBox()
{
    return mBox;
}

void Yummy::deleteYummy()
{
    mBox.x = UNDEFINED_X;
    mBox.y = UNDEFINED_Y;
    mBox.w = UNDEFINED_W;
    mBox.h = UNDEFINED_H;
    mType = NO_YUMMY;
}
