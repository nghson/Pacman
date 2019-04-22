#include "PathFinding.h"

PathFinding::PathFinding(Ghost ghost, Pacman pacman);
{
    sStart = ghost.getBox();
    sEnd = pacman.getBox();
    VEL = ghost.GHOST_VEL;
}

bool PathFinding::isEnd(SDL_Rect currentState)
{
    return ((currentState.x == sEnd.x) && (currentState.y == sEnd.y));
}

std::tuple<int, int, SDL_Rect> PathFinding::succAndCost(SDL_Rect state, int action)
{
    std::tuple<int, int, SDL_Rect> result;
    int cost;

    switch (action)
    {
    case MOVING_UP:
        SDL_Rect newState = {state.x, state.y - VEL, state.w, state.h};
        if (canMove(state, VEL, action)) cost = 1;
        else cost = INT_MAX;
        result = std::make_tuple(cost, action, newState);
        break;
    case MOVING_DOWN:
        SDL_Rect newState = {state.x, state.y + VEL, state.w, state.h};
        if (canMove(state, VEL, action)) cost = 1;
        else cost = INT_MAX;
        result = std::make_tuple(cost, action, newState);
        break;
    case MOVING_LEFT:
        SDL_Rect newState = {state.x - VEL, state.y, state.w, state.h};
        if (canMove(state, VEL, action)) cost = 1;
        else cost = INT_MAX;
        result = std::make_tuple(cost, action, newState);
        break;
    case MOVING_RIGHT:
        SDL_Rect newState {state.x + VEL, state.y, state.w, state.h};
        if (canMove(state, VEL, action)) cost = 1;
        else cost = INT_MAX;
        result = std::make_tuple(cost, action, newState);
        break;
    }
    return result;
}

std::vector<int> PathFinding::aStarSearch()
{
    //Tuple <cost, action, state> to add into frontier
    std::tuple<int, int, SDL_Rect> costActionState;

    //Action to add into explored
    int action;

    //Initialize explored (as vector) and frontier (as priority queue)
    vector<int> explored;
    priority_queue<std::tuple<int, int, SDL_Rect>, std::vector<std::tuple>, std::greater<int> > frontier;

    //Put the starting state in openList
    frontier.push(0, NOT_MOVING, sStart);

    //Loop until openList is empty
    while (!frontier.empty())
    {
        //Get pair with min cost from frontier
        costActionState = frontier.top();

        //Remove the pair with min cost from frontier
        frontier.pop();

        //If ghost has reached destination, terminate
        if (isEnd((costActionState->second)->first))
        {
            return explored;
        }

        //Generate 4 successors (up, down, left, right) and add into frontier
        for (int action = MOVING_UP; action < NOT_MOVING; action++)
        {
            frontier.push(succAndCost(std::get<2>(costActionState), action));
        }


    }
}
