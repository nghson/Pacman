#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Texture.h"
#include "Tile.h"
#include "Pacman.h"
#include "Yummy.h"

class Game
{
public:
    //Constructor
    Game();

    //Initialize SDL
    bool init();

    //Load texture
    bool loadTexture();

    //Load font text
    bool loadFont();

    //Set tiles
    bool setTiles(Tile* tiles[], Yummy* yummy[]);

    //Close SDL and free memory
    void close(Tile* tiles[], Yummy* yummy[]);

    //Play the game
    void play();

private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 840;
    const int SCREEN_HEIGHT = 620;
    const int PLAYSCREEN_WIDTH = 560;

    //Number of yummy = number of space tiles
    const int TOTAL_YUMMY = 300;

    //Current high score
    int highScore;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;

    //Font for text
    TTF_Font* font = NULL;

    //Color for font
    SDL_Color textColor = {255, 255, 255};

    //Textures for play screen
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

    //Texture for info screen
    Texture textYScoreTexture;
    Texture textYourScoreTexture;
    Texture textHScoreTexture;
    Texture textHighScoreTexture;
    Texture textLifeTexture;
    Texture lifeTexture;
    Texture logoTexture;

    //Texture for start/end screen
    Texture startEndLogoTexture;
    Texture textStartTexture;
    Texture textEndTexture;
    Texture textPlayAgainTexture;

    //Animation
    const int ANIMATION_FRAMES = 4;
    int frame;

    //Sprites
    SDL_Rect pacmanSpriteClips[4][4];
    SDL_Rect blinkySpriteClips[4][4];
    SDL_Rect clydeSpriteClips[4][4];
    SDL_Rect inkySpriteClips[4][4];
    SDL_Rect pinkySpriteClips[4][4];

    //Types of yummy
    enum
    {
        SMALL_YUMMY,
        NO_YUMMY,
        BIG_YUMMY
    };

    //Size of yummy
    const int SMALL_YUMMY_WIDTH = 4;
    const int SMALL_YUMMY_HEIGHT = 4;
    const int BIG_YUMMY_WIDTH = 8;
    const int BIG_YUMMY_HEIGHT = 8;

    //Tile constants
    const int TOTAL_TILES = 868; // 868 = 28*31
    const int TOTAL_TILE_TYPES = 2;

    //Tile dimensions
    const int TILE_WIDTH = 20;
    const int TILE_HEIGHT = 20;

    //Level dimensions
    const int LEVEL_WIDTH = 560;
    const int LEVEL_HEIGHT = 620;

    //Type of tiles
    const int BLANK_TILE = 9;
    const int WALL_TILE = 1;
    const int SPACE_TILE = 0;
};

#endif // GAME_H
