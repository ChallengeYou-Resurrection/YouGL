#include "Game.h"

#include <iostream>

#include "Game/OldFormat/OldFormatUtil.h"

int main(int argc, char** argv)
{
    //TODO Load a config file for resolution and other options
    //OldFormat::massConvertFilesBinaryFormat(); return 0;
    /*
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "conv")) {
                OldFormat::massConvertFilesBinaryFormat();
                return 0;
            }
        }
    }
    */
    Game game;
    game.run();

    return 0;
}