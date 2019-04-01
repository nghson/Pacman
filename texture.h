#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
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
    int mVel = 0;
};

#endif // TEXTURE_H
