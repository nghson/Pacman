#include "pacman.h"

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error: Unable to initialize SDL!\n");
        logError("SDL");
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!\n");
            success = false;
        }
        gWindow = SDL_CreateWindow("PACMAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Error: Unable to create window!\n");
            logError("SDL");
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Error: Unable to create renderer!\n");
                logError("SDL");
                success = false;
            }
        }
    }
    return success;
}

void logError(string errorType)
{
    switch (errorType)
    {
    case "SDL":
        printf("SDL Error: %s\n", SDL_GetError());
        return;
    case "IMG":
        printf("SDL_image Error: %s\n", IMG_GetError());
        return;
    default:
        printf("Undefined Error!\n");
        return;
    }
}

bool loadMedia(LTexture gTexture, std::string path)
{
    bool success = true;
    if (gTexture.loadFromFile(path) == false)
    {
        printf("Error: Unable to load media to texture!\n");
        logError("SDL");
        success = false;
    }
    return success;
}

bool setWallTile(WallTile* wallTiles[])
{
    bool success = true;
    int x = 0, y = 0;

    std::ifstream Map()
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
}

WallTile::WallTile(int x, int y)
{
	mBox.x = x;
	mBox.y = y;
	mBox.w = tileWidth;
	mBox.h = tileHeight;
}

void WallTile::render(int x, int y)
{

}

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

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface);
    if (newTexture == NULL)
    {
        printf("Failed to create texture from %s!", path.c_str());
        logError("IMG");
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render(int x, int y, )
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

int main(int argc, char* args[])
{
	return 0;
}









