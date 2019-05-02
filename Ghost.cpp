#include "Ghost.h"

//Implement hash function so we can put SDL_Rect into an unordered_map
namespace std {
template <> struct hash<SDL_Rect> {
  typedef SDL_Rect argument_type;
  typedef std::size_t result_type;
  std::size_t operator()(const SDL_Rect& id) const noexcept {
    return std::hash<int>()(id.x ^ (id.y << 4));
  }
};
}

//Overloading ==, != and <
bool operator == (SDL_Rect a, SDL_Rect b)
{
    return (a.x == b.x && a.y == b.y);
}
bool operator != (SDL_Rect a, SDL_Rect b)
{
    return ((a.x != b.x) || (a.y != b.y));
}
bool operator < (SDL_Rect a, SDL_Rect b)
{
    return (std::tie(a.x, a.y) < std::tie(b.x, b.y));
}

Ghost::Ghost(int _x, int _y)
{
    //Initialize position of ghost
    pos = {_x, _y, GHOST_WIDTH, GHOST_HEIGHT};

    //Initialize direction
    dir = NOT_MOVING;
}

int Ghost::heuristic(SDL_Rect a, SDL_Rect b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

void Ghost::render(Texture& spriteSheetTexture, SDL_Rect spriteClips[][4], int frame, SDL_Renderer* renderer)
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
        SDL_Rect* currentClip = &spriteClips[0][frame/4];
        spriteSheetTexture.render(pos.x, pos.y, renderer, currentClip);
    }
}

SDL_Rect Ghost::getPos()
{
    return pos;
}

void Ghost::move(SDL_Rect pacmanPos, Tile* tiles[])
{
    //Path from A*
    std::vector<SDL_Rect> path = aStarPath(pos, pacmanPos, tiles);

    //Where the ghost supposed to be next?
    SDL_Rect nextPos = path[1];

    //Move the ghost accordingly
    if (pos.x < nextPos.x && canMove(pos, MOVING_RIGHT, tiles)) pos.x += GHOST_VEL;
    else if (pos.x > nextPos.x && canMove(pos, MOVING_LEFT, tiles)) pos.x -= GHOST_VEL;
    else if (pos.y > nextPos.y && canMove(pos, MOVING_UP, tiles)) pos.y -= GHOST_VEL;
    else if (pos.y < nextPos.y && canMove(pos, MOVING_DOWN, tiles)) pos.y += GHOST_VEL;
}

//A* Search
std::vector<SDL_Rect> Ghost::aStarPath(SDL_Rect start, SDL_Rect goal, Tile* tiles[])
{
    //Storing parent tile of a tile
    std::unordered_map<SDL_Rect, SDL_Rect> parent;

    //Storing cost so far
    std::unordered_map<SDL_Rect, double> cost;

    //Priority queue
    PriorityQueue<SDL_Rect, double> frontier;

    //Initialize parent and cost of current ghost position
    parent[start] = start;
    cost[start] = 0;

    //Initialize frontier
    frontier.put(start, 0);

    while (!frontier.empty())
    {
        //Get the position with largest priority and delete it
        SDL_Rect current = frontier.get();

        //If ghost has reached destination
        if (current == goal) break;

        //CHECK ALL POSSIBLE MOVING DIRECTIONS

        //Up
        double newCostUP = cost[current] + GHOST_VEL;
        SDL_Rect nextUP = {current.x, current.y - GHOST_VEL, current.w, current.h};
        //If the next position is not explored or the newCost is smaller than the previous calculated cost
        if (!cost.count(nextUP) || newCostUP < cost[nextUP])
        {
            //If cannot move to the position, the cost is infinity
            if (!canMove(current, MOVING_UP, tiles)) newCostUP = DBL_MAX;
            cost[nextUP] = newCostUP;
            frontier.put(nextUP, newCostUP + heuristic(nextUP, goal));
            parent[nextUP] = current;
        }

        //Down
        double newCostDOWN = cost[current] + GHOST_VEL;
        SDL_Rect nextDOWN = {current.x, current.y + GHOST_VEL, current.w, current.h};
        //If the next position is not explored or the newCost is smaller than the previous calculated cost
        if (!cost.count(nextDOWN) || newCostDOWN < cost[nextDOWN])
        {
            //If cannot move to the position, the cost is infinity
            if (!canMove(current, MOVING_DOWN, tiles)) newCostDOWN = DBL_MAX;
            cost[nextDOWN] = newCostDOWN;
            frontier.put(nextDOWN, newCostDOWN + heuristic(nextDOWN, goal));
            parent[nextDOWN] = current;
        }

        //Left
        double newCostLEFT = cost[current] + GHOST_VEL;
        SDL_Rect nextLEFT = {current.x - GHOST_VEL, current.y, current.w, current.h};
        //If the next position is not explored or the newCost is smaller than the previous calculated cost
        if (!cost.count(nextLEFT) || newCostLEFT < cost[nextLEFT])
        {
            //If cannot move to the position, the cost is infinity
            if (!canMove(current, MOVING_LEFT, tiles)) newCostLEFT = DBL_MAX;
            cost[nextLEFT] = newCostLEFT;
            frontier.put(nextLEFT, newCostLEFT + heuristic(nextLEFT, goal));
            parent[nextLEFT] = current;
        }

        //Right
        double newCostRIGHT = cost[current] + GHOST_VEL;
        SDL_Rect nextRIGHT = {current.x + GHOST_VEL, current.y, current.w, current.h};
        //If the next position is not explored or the newCost is smaller than the previous calculated cost
        if (!cost.count(nextRIGHT) || newCostRIGHT < cost[nextRIGHT])
        {
            //If cannot move to the position, the cost is infinity
            if (!canMove(current, MOVING_RIGHT, tiles)) newCostRIGHT = DBL_MAX;
            cost[nextRIGHT] = newCostRIGHT;
            frontier.put(nextRIGHT, newCostRIGHT + heuristic(nextRIGHT, goal));
            parent[nextRIGHT] = current;
        }
    }

    //Path taken by A*
    std::vector<SDL_Rect> path;

    //From the pacman position back to ghost position
    SDL_Rect current = goal;

    path.push_back(current);

    //Construct path from pacman to ghost
    while (current != start)
    {
        current = parent[current];
        path.push_back(current);
    }

    //Reverse the list, so that the path is from ghost position to pacman position
    std::reverse(path.begin(), path.end());

    return path;
}

