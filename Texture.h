#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Texture wrapper class
class Texture
{
public:
    //Initializes variables
    Texture();

    //Deallocates memory
    ~Texture();

    //Loads image at specified path
    bool loadFromFile(SDL_Renderer* renderer, std::string path);

    //Deallocates texture
    void free();

    //Renders texture at given point
    void render(int x, int y, SDL_Renderer* renderer);

    //Get image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // TEXTURE_H
