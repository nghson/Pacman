#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Texture.h"
#include "Tile.h"
#include "Pacman.h"
#include "Yummy.h"

class Game
{
private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 560;
    const int SCREEN_HEIGHT = 620;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Textures
    Texture blankTexture;
    Texture pacmanTexture;
    Texture wallTexture;
    Texture spaceTexture;
    Texture smallYummyTexture;
    Texture bigYummyTexture;
    Texture blinkyTexture;
    Texture clydeTexture;
    Texture inkyTexture;
    Texture pinkyTexture;

    //Animation
    const int ANIMATION_FRAMES = 2;
    int frame;

    //Pacman animation
    SDL_Rect pacmanSpriteClips[4][4];

public:
    //Constructor
    Game();

    //Initialize SDL
    bool init();

    //Load texture
    bool loadTexture();

    //Set tiles
    bool setTiles(Tile* tiles[], Yummy* yummy[]);

    //Close SDL and free memory
    ~Game(Tile* tiles[], Yummy* yummy[]);

    //Play the game
    void play();

};

#endif // GAME_H
