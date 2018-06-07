#include "Game.h"

#include <iostream>

int main()
{
    //TODO Load a config file for resolution and other options

    try {
        Game game;
        game.run();
    }
    catch (std::exception& e) {
        std::cout << "Exception:\n" << e.what();
        std::cin.ignore();
        return -1;
    }
    return 0;
}
