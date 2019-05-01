#include "Yummy.h"

Yummy::Yummy(int _x, int _y, int _type)
{
    //Get the yummy type
    type = _type;

    //Set the positions and sizes of yummy
    switch (type)
    {
    case SMALL_YUMMY:
        box.x = _x;
        box.y = _y;
        box.w = YUMMY_WIDTH;
        box.h = YUMMY_HEIGHT;
        break;
    case BIG_YUMMY:
        box.x = _x;
        box.y = _y;
        box.w = YUMMY_WIDTH;
        box.h = YUMMY_HEIGHT;
        break;
    case NO_YUMMY:
        box.x = 0;
        box.y = 0;
        box.w = 0;
        box.h = 0;
        break;
    }
}

void Yummy::render(Texture& yummyTexture, SDL_Renderer* renderer)
{
    yummyTexture.render(box.x, box.y, renderer);

}

int Yummy::getType()
{
    return type;
}

SDL_Rect Yummy::getBox()
{
    return box;
}

void Yummy::deleteYummy()
{
    //All coordinates, width and height become 0
    box.x = 0;
    box.y = 0;
    box.w = 0;
    box.h = 0;
    type = NO_YUMMY;
}
