#include "Game.h"

#include <iostream>

void runGame()
{
    Game game;
    game.run();
}

int main(int argc, char** argv)
{
    //TODO Load a config file for resolution and other options

    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "conv") {

            }
        }
        runGame();
    }
    else {
        runGame();
    }
    return 0;
}
