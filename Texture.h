#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
    void render(int x, int y, SDL_Rect* clip = NULL, SDL_Renderer* renderer);

    //Get width
    int getWidth();

    //Get height
    int getHeight();

    //Reset dimensions
    void resetDim(int _width, int _height);

private:
    //The actual hardware texture
    SDL_Texture* texture;

    //Image dimensions
    int width;
    int height;
};

#endif // TEXTURE_H
