#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

//Texture wrapper class
class Texture
{
public:
    //Constructor
    Texture();

    //Destructor: free memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* renderer, std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

    //Get width
    int getWidth();

    //Get height
    int getHeight();

    //Reset dimensions
    void resetDim(int _width, int _height);

    //Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font, SDL_Renderer* renderer);

private:
    //The actual hardware texture
    SDL_Texture* texture;

    //Texture width
    int width;

    //Texture height
    int height;
};

#endif // TEXTURE_H
