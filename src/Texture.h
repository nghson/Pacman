#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

//Texture wrapper class
class Texture
{
public:
    //Constructor
    Texture();

    //Destructor: free memory
    ~Texture();

    //Loads BMP image at specified path
    bool loadFromFileBMP(SDL_Renderer* renderer, std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip = NULL);

    //Get width
    int getWidth();

    //Get height
    int getHeight();

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
