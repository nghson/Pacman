#include "game.h"

void logError(int errorType)
{
    switch (errorType)
    {
    case SDLERROR:
        printf("SDL Error: %s\n", SDL_GetError());
        return;
    case IMGERROR:
        printf("SDL_image Error: %s\n", IMG_GetError());
        return;
    default:
        printf("Undefined Error!\n");
        return;
    }
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error: Unable to initialize SDL!\n");
        logError(SDLERROR);
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
            logError(SDLERROR);
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Error: Unable to create renderer!\n");
                logError(SDLERROR);
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
                if((IMG_Init(imgFlags)) != (imgFlags))
                {
                    printf("Error: Unable to initialize SDL_image support for JPG and PNG!\n");
                    logError(IMGERROR);
                    success = false;
                }
            }
        }
    }
    return success;
}

bool setTiles(Tile* tiles[], std::string path)
{
    bool success = true;
    int x = 0, y = 0;

    std::ifstream Map(path);

    if (!Map.is_open())
    {
        printf("Unable to load map file!\n");
        success = false;
    }
    else
    {
        for (int i = 0; i < TOTAL_TILES; i++)
        {
            int tileType;

            // Currently there is two tile types:
            // 1 (wall) and 0 (space)
            Map >> tileType;

            if (Map.fail())
            {
                printf("Error: Unexpected end of file when loading map!\n");
                success = false;
                break;
            }

            if ((tileType >= 0) && (tileType < TYPES_OF_TILES))
            {
                tiles[i] = new Tile(x, y, tileType);
            }
            else
            {
                printf("Invalid tile type when loading map at %d!\n", i);
                success = false;
                break;
            }

            x += TILE_WIDTH;
            if (x >= SCREEN_WIDTH)
            {
                x = 0;
                y += TILE_HEIGHT;
            }
        }
    }
    Map.close();
    return success;
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

bool loadTextureMedia(int textureType, std::string path)
{
    bool success = true;
    switch (textureType)
    {
    case WALL:
        if (gWallTexture.loadFromFile(path) == false)
        {
            printf("Error: Unable to load media to texture!\n");
            success = false;
        }
        break;
    case SPACE:
        if (gSpaceTexture.loadFromFile(path) == false)
        {
            printf("Error: Unable to load media to texture!\n");
            success = false;
        }
        break;
    case PACMAN:
        if (gPacmanTexture.loadFromFile(path) == false)
        {
            printf("Error: Unable to load media to texture!\n");
            success = false;
        }
        break;
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
    gSpaceTexture.free();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if (!init())
    {
        printf("UNABLE TO INITIALIZE!\n");
    }
    else
    {
        Tile* tileSet[TOTAL_TILES];
        if (!loadTextureMedia(WALL, "data/walltile-test.bmp") ||
            !loadTextureMedia(SPACE, "data/spacetile-test.bmp") ||
            !loadTextureMedia(PACMAN, "data/pacman-test.bmp"))
        {
            printf("UNABLE TO LOAD MEDIA TO TEXTURE!\n");
        }
        else
        {
            if (!setTiles(tileSet, "data/Map.txt"))
            {
                printf("UNABLE TO SET THE TILES!\n");
            }
            else
            {
                bool quit = false;
                SDL_Event e;
                while (!quit)
                {
                    while (SDL_PollEvent(&e) != 0)
                    {
                        if (e.type == SDL_QUIT)
                        {
                            quit = true;
                        }
                        pacman.handleEvent(e);
                    }
                    pacman.move(tileSet, SCREEN_WIDTH, SCREEN_HEIGHT);

                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(gRenderer);

                    for (int i = 0; i < TOTAL_TILES; i++)
                    {
                        tileSet[i]->render(tileSet[i]->getType());
                    }
                    pacman.render();

                    SDL_RenderPresent(gRenderer);
                }
            }
        }
        close(tileSet);
    }
	return 0;
}









