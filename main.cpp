#include "main.h"

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

void logError(std::string errorType)
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

bool loadMedia(LTexture gTexture, WallTile* wallTiles[], std::string path)
{
    bool success = true;
    // Load image for texture
    if (gTexture.loadFromFile(path) == false)
    {
        printf("Error: Unable to load media to texture!\n");
        logError("SDL");
        success = false;
    }
    // Load Pacman.map for map
    if (!setWallTile(wallTiles))
    {
        printf("Error: Unable to load wall tile map!\n");
        success = false;
    }
    return success;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
}

int main(int argc, char* args[])
{
	return 0;
}









