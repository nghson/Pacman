#include "Game.h"

int main(int argc, char* args[])
{
    //Set random seed;
    srand(time(NULL));

    Game playPacman = Game();
    playPacman.play();
    return 0;
}
