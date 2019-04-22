#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <SDL2/SDL.h>
#include <climits>
#include "Pacman.h"
#include "Ghost.h"
#include "Tile.h"

class PathFinding
{
private:
    //Cost of wall
    static const int wallCost = 1000000;

    //Cost of space
    static const int spaceCost = 1;

    //To record a state
    struct State
    {
        //Parent position of the state
        SDL_Rect parentPosition;

        //Position of the state
        SDL_Rect position;

        //Cost so far
        int cost;

        //Action to reach this state
        int action;

        //Constructor
        State(SDL_Rect _parentPosition, SDL_Rect _position, int _cost, int _action);

        //Overloading "<" for std::set: compare cost for order
        bool operator < (const State& s) const;

        //Overloading "==" for std::set: finding elements with the same position
        bool operator == (const State& s) const;
    };

    //Indicators of actions
    enum
    {
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT,
        NOT_MOVING
    };

    //Pacman position
    SDL_Rect pacmanPosition;

    //Initial ghost position
    SDL_Rect ghostPosition

    //Velocity
    int VEL;

public:
    //Constructor
    PathFinding(Ghost ghost, Pacman pacman);

    //Whether the ghost has reached the final position
    bool isEnd(SDL_Rect currentState);

    //Return heuristic (Manhattan distance) from provided state to pacman (note that the result is always an integer)
    int h(SDL_Rect state, SDL_Rect pacman);

    //Return cost, action and new state as a tuple
    State succAndCost(State state, int action);

    //Uniform Cost Search returns a list of actions for ghost
    vector<int> uniformCostSearch();
};

//Overload "<" so that we can use priority_queue<State>
bool operator<(State& s1, State& s2)
{
    return (s1.cost < s2.cost);
}

#endif // PATHFINDING_H
