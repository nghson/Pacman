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
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
                if((IMG_Init(imgFlags)) != (imgFlags))
                {
                    printf("Error: Unable to initialize SDL_image support for JPG and PNG!\n");
                    logError("IMG");
                    success = false;
                }
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

bool loadTileMedia(Tile* tiles[], std::string path)
{
    bool success = true;
    if (!setTiles(tiles, path.c_str()))
    {
        printf("Error: Unable to load wall tile map!\n");
        success = false;
    }
    return success;
}

bool loadTextureMedia(LTexture& gTexture, std::string path)
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

void close(Tile* tiles[])
{
    // Deallocate tiles
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (tiles[i] == NULL)
        {
            delete tiles[i];
            tiles[i] = NULL;
        }
    }

    gWallTexture.free();
    gPacmanTexture.free();
    gBlinkyTexture.free();
    gClydeTexture.free();
    gInkeyTexture.free();
    gBigYummy.free();
    gSmallYummy.free();
    gCherry.free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x, leftB = b.x;
    int rightA = a.x + a.w, rightB = b.x + b.w;
    int topA = a.y, topB = b.y;
    int bottomA = a.y + a.h, bottomB = b.y + b.h;

    if(bottomA <= topB)
    {
        return false;
    }

    if(topA >= bottomB)
    {
        return false;
    }

    if(rightA <= leftB)
    {
        return false;
    }

    if(leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool setTiles(Tile* tiles[], std::string path)
{
    bool success = true;
    int x = 0, y = 0;

    std::ifstream Map(path.c_str());

    if (!Map.is_open())
    {
        printf("Error: Unable to load map file!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < TOTAL_TILES; i++)
        {
            int tileType;
            // Currently there is two tile types: 1 (wall) and 0 (space)
            Map >> tileType;

            if (Map.fail())
            {
                printf("Error: Unexpected end of file when loading map!\n");
                success = false;
                break;
            }

            if (tileType >= 0) && (tileType < TYPES_OF_TILES)
            {
                tiles[i] = new Tile(x, y, tileType);
            }
            else
            {
                printf("Error: Invalid tile type when loading map at %d!\n", i);
                success = false;
                break;
            }

            x += TILE_WIDTH;
            if (x >= LEVEL_WIDTH)
            {
                x = 0;
                y += TILE_HEIGHT;
            }
        }
    }
    Map.close();
    return success;
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (tiles[i]->getType() == TILE_WALL)
        {
            if (checkCollision(box, tiles[i]->getBox()))
            {
                return true;
            }
        }
    }
    return false;
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("UNABLE TO INITIALIZE!\n");
    }
    else
    {
        if (!loadTextureMedia())
    }
	return 0;
}









