#include "Pacman.h"

Pacman::Pacman(int _x, int _y, const int TOTAL_YUMMY)
{
    //Initialize the collision box
    pos.x = _x;
    pos.y = _y;
	pos.w = PACMAN_WIDTH;
	pos.h = PACMAN_HEIGHT;

    //Initialize the velocity
    velX = 0;
    velY = 0;

    //Initialize ePending
    ePending = NOT_MOVING;

    //Initialize number of yummy
    yummyLeft = TOTAL_YUMMY;

    //Initialize direction
    dir = NOT_MOVING;

    //Initialize score
    score = 0;
}

void Pacman::move(Tile *tiles[], int PLAYSCREEN_WIDTH)
{
    //Move pacman left or right
    pos.x += velX;

    //If pacman touched a wall
    if (touchesWall(pos, tiles))
    {
        //move back
        pos.x -= velX;
    }

    //Teleport
    if (pos.x < 0) pos.x = PLAYSCREEN_WIDTH - PACMAN_WIDTH;
    else if (pos.x + PACMAN_WIDTH > PLAYSCREEN_WIDTH) pos.x = 0;

    //Move pacman up or down
    pos.y += velY;

    //If pacman touched a wall
    if (touchesWall(pos, tiles))
    {
        //move back
        pos.y -= velY;
    }
}

void Pacman::render(Texture& spriteSheetTexture, SDL_Rect spriteClips[][4], int frame, SDL_Renderer* renderer)
{
    if (dir == MOVING_LEFT)
    {
        SDL_Rect* currentClip = &spriteClips[0][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_DOWN)
    {
        SDL_Rect* currentClip = &spriteClips[1][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_RIGHT)
    {
        SDL_Rect* currentClip = &spriteClips[2][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == MOVING_UP)
    {
        SDL_Rect* currentClip = &spriteClips[3][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
    if (dir == NOT_MOVING)
    {
        SDL_Rect* currentClip = &spriteClips[2][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
}

void Pacman::handleEvent(SDL_Event& e, Tile* tiles[])
{
    //If a key was pressed
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        //Adjust the velocity
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            if (canMove(pos, MOVING_UP, tiles))
            {
                velY = -PACMAN_VEL;
                velX = 0;
                ePending = NOT_MOVING;
                dir = MOVING_UP;
                return;
            }
            else
            {
                ePending = MOVING_UP;
                return;
            }
            break;
        case SDLK_DOWN:
            if (canMove(pos, MOVING_DOWN, tiles))
            {
                velY = PACMAN_VEL;
                velX = 0;
                ePending = NOT_MOVING;
                dir = MOVING_DOWN;
                return;
            }
            else
            {
                ePending = MOVING_DOWN;
                return;
            }
            break;
        case SDLK_LEFT:
            if (canMove(pos, MOVING_LEFT, tiles))
            {
                velX = -PACMAN_VEL;
                velY = 0;
                ePending = NOT_MOVING;
                dir = MOVING_LEFT;
                return;
            }
            else
            {
                ePending = MOVING_LEFT;
                return;
            }
            break;
        case SDLK_RIGHT:
            if (canMove(pos, MOVING_RIGHT, tiles))
            {
                velX = PACMAN_VEL;
                velY = 0;
                ePending = NOT_MOVING;
                dir = MOVING_RIGHT;
                return;
            }
            else
            {
                ePending = MOVING_RIGHT;
                return;
            }
            break;
        }
    }
}

void Pacman::handlePending(Tile* tiles[])
{
    //Check for pending key
    if (ePending != NOT_MOVING)
    {
        switch (ePending)
        {
        case MOVING_UP:
            if (canMove(pos, MOVING_UP, tiles))
            {
                velY = -PACMAN_VEL;
                velX = 0;
                ePending = NOT_MOVING;
                dir = MOVING_UP;
                return;
            }
            break;
        case MOVING_DOWN:
            if (canMove(pos, MOVING_DOWN, tiles))
            {
                velY = PACMAN_VEL;
                velX = 0;
                ePending = NOT_MOVING;
                dir = MOVING_DOWN;
                return;
            }
            break;
        case MOVING_LEFT:
            if (canMove(pos, MOVING_LEFT, tiles))
            {
                velX = -PACMAN_VEL;
                velY = 0;
                ePending = NOT_MOVING;
                dir = MOVING_LEFT;
                return;
            }
            break;
        case MOVING_RIGHT:
            if (canMove(pos, MOVING_RIGHT, tiles))
            {
                velX = PACMAN_VEL;
                velY = 0;
                ePending = NOT_MOVING;
                dir = MOVING_RIGHT;
                return;
            }
            break;
        }
    }
}

bool Pacman::lose(Ghost ghost)
{
    return checkCollision(ghost.getPos(), pos);
}

bool Pacman::win()
{
    return (yummyLeft <= 0);
}

std::vector<int> Pacman::eatYummy(Yummy* yummy[], const int TOTAL_TILES)
{
    std::vector<int> eatenYummy;
    //Check if pacman has eaten which yummy
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (checkCollision(pos, yummy[i]->getBox()))
        {
            eatenYummy.push_back(i);

            //If pacman ate smal yummy, score += 10
            if (yummy[i]->getType() == 0) score += 10;

            //If pacman ate big yummy, score += 100
            if (yummy[i]->getType() == 2) score += 100;
        }
    }
    //Update the number of yummy left
    yummyLeft -= eatenYummy.size();

    return eatenYummy;
}

SDL_Rect Pacman::getPos()
{
    return pos;
}

int Pacman::getScore()
{
    return score;
}
