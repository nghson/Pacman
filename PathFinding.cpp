#include "PathFinding.h"

PathFinding::State::State(SDL_Rect _parentPosition, SDL_Rect _position, int _cost, int _action)
{
    parentPosition = _parentPosition;
    position = _position;
    cost = _cost;
    action = _action;
}

bool PathFinding::State::operator < (const State& s) const
{
    return (cost < s.cost);
}

bool PathFinding::State::operator == (const State& s) const
{
    return (position == s.position);
}

PathFinding::PathFinding(Ghost ghost, Pacman pacman);
{
    pacmanPosition = pacman.getBox();
    ghostPosition = ghost.getBox();
    VEL = ghost.GHOST_VEL;
}

bool PathFinding::isEnd(SDL_Rect currentPosition)
{
    return ((currentPosition.x == pacmanPosition.x) && (currentPosition.y == pacmanPosition.y));
}

State PathFinding::succAndCost(State state, int action)
{
    int newCost;
    SDL_Rect newPosition;

    switch (action)
    {
    case MOVING_UP:
        //New position
        newPosition = {state.x, state.y - VEL, state.w, state.h};

        //New cost with heuristic
        if (canMove(state, VEL, action)) newCost = (spaceCost + state.cost);
        else newCost = (wallCost + state.cost);

        break;
    case MOVING_DOWN:
        //New position
        newPosition = {state.x, state.y + VEL, state.w, state.h};

        //New cost with heuristic
        if (canMove(state, VEL, action)) newCost = (spaceCost + state.cost);
        else newCost = (wallCost + state.cost);

        break;
    case MOVING_LEFT:
        //New position
        newPosition = {state.x - VEL, state.y, state.w, state.h};

        //New cost with heuristic
        if (canMove(state, VEL, action)) newCost = (spaceCost + state.cost);
        else newCost = (wallCost + state.cost);

        break;
    case MOVING_RIGHT:
        //New position
        newPosition = {state.x + VEL, state.y, state.w, state.h};

        //New cost with heuristic
        if (canMove(state, VEL, action)) newCost = (spaceCost + state.cost);
        else newCost = (wallCost + state.cost);

        break;
    }
    return State(state.position, newPosition, newCost, action);
}

int PathFinding::h(SDL_Rect state)
{
    return abs(state.x - sEnd.x) + abs(state.y - sEnd.y);
}

std::vector<State> PathFinding::uniformCostSearch()
{
    //Initialize closedList (as vector) and openList (as set)
    std::vector<State> closedList;
    std::set<State> openList;

    //Put the starting state in openList, with undefined parentPosition == undefinedPosition
    SDL_Rect undefinedPosition = {0, 0, 0, 0};
    openList.insert(State(undefinedPosition, ghostPosition, 0, NOT_MOVING));

    //Loop until openList is empty
    while (!openList.empty())
    {
        //Get the node with lowest cost in openList
        State s = *openList.begin();

        //Remove that node
        openList.erase(openList.begin());

        //If ghost has reached the destination
        if (isEnd(s.position))
        {
            return closedList;
        }

        //Add s into closedList
        closedList.insert(s);

        for (int action = 0; action < NOT_MOVING; action++)
        {
            State ss = succAndCost(s, action);
            if (!closedList.find(ss))
            {
                openList.insert(ss);
            }
        }
    }
}
