#include <iostream>

#include "CYWebParser.h"

int main(int argc, char** argv)
{
    CYLevel* cyLevel = CYWebParser::loadFileFromWebsite(257);

    cyLevel->destroyObjects();
    delete cyLevel;
    return 1;
}
