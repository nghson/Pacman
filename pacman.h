#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

const int SCREEN_HEIGHT = 1280;
const int SCREEN_WIDTH = 720;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gWallTileTexture = NULL;

void logError();
bool init();
bool loadMedia();
void close();

class LTexture
{
private:
    LTexture();
    ~LTexture();

    bool loadFromFile(std::string path);

    void free();

    void render(int x, int y);

    int getWidth();
    int getHeight();
private:
    SDL_Texture* mTexture;

    int mWidth;
    int mHeight;
};

LTexture gTileTexture;

class WallTile
{
public:
    WallTile(int x, int y, int tileWidth, tileHeight);

    // Render the wall tile
    bool loadMedia(std::string path);
    void render();

    // Get the collision box
    SDL_Rect getBox();
private:
    // Attributes of the wall tile
    SDL_Rect mBox;
};
