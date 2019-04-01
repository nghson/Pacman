#include "texture.h"

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = SDL_LoadBMP(path.c_str());
    if (loadSurface == NULL)
    {
        printf("Failed to load image %s!\n", path.c_str());
        logError("SDL");
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
        if (newTexture == NULL)
        {
            printf("Failed to create texture from %s!", path.c_str());
            logError("IMG");
        }
        else
        {
            mWidth = loadSurface->w;
            mHeight = loadSurface->h;
        }
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render(int x, int y)
{
    SDL_Rect renderRectDst = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderRectDst);
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
