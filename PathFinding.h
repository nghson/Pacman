#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <climits>
#include <cmath>
#include <SDL2/SDL.h>
#include <queue>
#include "Pacman.h"
#include "Ghost.h"
#include "Tile.h"

class PathFinding
{
private:
    //Indicators of actions
    enum
    {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        NOT_MOVING
    };

    //Start state, which is the current ghost's position
    SDL_Rect sStart;

    //End state, which is the current pacman's position
    SDL_Rect sEnd;

    //Velocity
    int VEL;

public:
    //Constructor
    PathFinding(Ghost ghost, Pacman pacman);

    //Whether the ghost has reached the final position
    bool isEnd(SDL_Rect currentState);

    //Return cost, action and new state as a tuple
    std::tuple<int, int, SDL_Rect> succAndCost(SDL_Rect state, int action, Tile* tiles[])

    //A* Search returns a list of actions for ghost
    vector<int> aStarSearch();
};



#endif // PATHFINDING_H
