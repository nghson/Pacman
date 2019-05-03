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

//Overloading == for unordered_map
bool operator == (SDL_Rect a, SDL_Rect b)
{
    return (a.x == b.x && a.y == b.y);
}

//Overloading !=
bool operator!=(SDL_Rect a, SDL_Rect b)
{
    return (a.x != b.x || a.y != b.y);
}

//Overloading <
bool operator < (SDL_Rect a, SDL_Rect b)
{
    return (std::tie(a.x, a.y) < std::tie(b.x, b.y));
}

Ghost::Ghost(int _x, int _y, int _name, int _movingMode)
{
    //Save initial position for resetPos()
    initPos = {_x, _y, GHOST_WIDTH, GHOST_HEIGHT};

    //Initialize position of ghost
    pos = initPos;

    //Initialize direction
    dir = NOT_MOVING;

    //Initialize moving mode
    movingMode = _movingMode;

    //Set name
    name = _name;
}

void Ghost::resetPos()
{
    pos.x = initPos.x;
    pos.y = initPos.y;
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

void Ghost::move(SDL_Rect goal, Tile* tiles[])
{
    if (movingMode == CHASE)
    {
        //Path from A*
        std::vector<SDL_Rect> path = aStarPath(pos, goal, tiles);

        //Where the ghost supposed to be next?
        SDL_Rect nextPos = path[1];

        //Move the ghost accordingly
        if (pos.x < nextPos.x && canMove(pos, MOVING_RIGHT, tiles)) pos.x += GHOST_VEL;
        else if (pos.x > nextPos.x && canMove(pos, MOVING_LEFT, tiles)) pos.x -= GHOST_VEL;
        else if (pos.y > nextPos.y && canMove(pos, MOVING_UP, tiles)) pos.y -= GHOST_VEL;
        else if (pos.y < nextPos.y && canMove(pos, MOVING_DOWN, tiles)) pos.y += GHOST_VEL;
    }
    else if (movingMode == RANDOM)
    {
        int path = randomPath(tiles);
        switch (path)
        {
        case MOVING_UP:
            pos.y -= GHOST_VEL;
            break;
        case MOVING_DOWN:
            pos.y += GHOST_VEL;
            break;
        case MOVING_LEFT:
            pos.x -= GHOST_VEL;
            break;
        case MOVING_RIGHT:
            pos.x += GHOST_VEL;
            break;
        }
    }
    else if (movingMode == STUPID)
    {
        int path = stupidPath(goal, tiles);
        switch (path)
        {
        case MOVING_UP:
            pos.y -= GHOST_VEL;
            break;
        case MOVING_DOWN:
            pos.y += GHOST_VEL;
            break;
        case MOVING_LEFT:
            pos.x -= GHOST_VEL;
            break;
        case MOVING_RIGHT:
            pos.x += GHOST_VEL;
            break;
        case NOT_MOVING:
            break;
        }
    }

    //Handle teleport
    if (pos.x > 560 + GHOST_WIDTH) pos.x = 0;
    else if (pos.x < 0) pos.x = 560 - GHOST_WIDTH;
}

int Ghost::stupidPath(SDL_Rect goal, Tile* tiles[])
{
    const int distUP = heuristic(goal, {pos.x, pos.y - GHOST_VEL, pos.w, pos.h});
    const int distDOWN = heuristic(goal, {pos.x, pos.y + GHOST_VEL, pos.w, pos.h});
    const int distLEFT = heuristic(goal, {pos.x - GHOST_VEL, pos.y, pos.w, pos.h});
    const int distRIGHT = heuristic(goal, {pos.x + GHOST_VEL, pos.y, pos.w, pos.h});

    int distMIN = std::min(std::min(distUP, distDOWN), std::min(distLEFT, distRIGHT));
    if (distMIN == distUP && canMove(pos, MOVING_UP, tiles)) return MOVING_UP;
    else if (distMIN == distDOWN && canMove(pos, MOVING_DOWN, tiles)) return MOVING_DOWN;
    else if (distMIN == distLEFT && canMove(pos, MOVING_LEFT, tiles)) return MOVING_LEFT;
    else if (distMIN == distRIGHT && canMove(pos, MOVING_RIGHT, tiles)) return MOVING_RIGHT;
    else return NOT_MOVING;
}

int Ghost::randomPath(Tile* tiles[])
{
    int randomMove;

    //Set the random seed
    if (name == BLINKY) srand(time(NULL) + 1234);
    else if (name == CLYDE) srand(time(NULL) + 2345);
    else if (name == INKY) srand(time(NULL) + 3456);
    else if (name == PINKY) srand(time(NULL) + 54941);

    //Get a random number in the range [0,3]
    int random = rand() % 4;

    //Choose the move of the ghost randomly
    if (random == MOVING_UP && canMove(pos, MOVING_UP, tiles)) randomMove = MOVING_UP;
    else if (random == MOVING_DOWN && canMove(pos, MOVING_DOWN, tiles)) randomMove = MOVING_DOWN;
    else if (random == MOVING_LEFT && canMove(pos, MOVING_LEFT, tiles)) randomMove = MOVING_LEFT;
    else if (random == MOVING_RIGHT && canMove(pos, MOVING_RIGHT, tiles)) randomMove = MOVING_RIGHT;
    else randomMove = NOT_MOVING;

    return randomMove;
}

//A* Search
std::vector<SDL_Rect> Ghost::aStarPath(SDL_Rect start, SDL_Rect goal, Tile* tiles[])
{
    //Storing parent tile of a tile
    std::unordered_map<SDL_Rect, SDL_Rect> parent;

    //Storing cost so far
    std::unordered_map<SDL_Rect, double> cost;

    //Element of priority_queue is pair<priority, position>
    typedef std::pair<double, SDL_Rect> element;

    //Priority queue
    std::priority_queue<element, std::vector<element>, std::greater<element> > frontier;

    //Initialize parent and cost of current ghost position
    parent[start] = start;
    cost[start] = 0;

    //Initialize frontier
    frontier.emplace(0, start);

    while (!frontier.empty())
    {
        //Get the position with largest priority and delete it
        SDL_Rect current = frontier.top().second;
        frontier.pop();

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
            frontier.emplace(newCostUP + heuristic(nextUP, goal), nextUP);
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
            frontier.emplace(newCostDOWN + heuristic(nextDOWN, goal), nextDOWN);
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
            frontier.emplace(newCostLEFT + heuristic(nextLEFT, goal), nextLEFT);
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
            frontier.emplace(newCostRIGHT + heuristic(nextRIGHT, goal), nextRIGHT);
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
