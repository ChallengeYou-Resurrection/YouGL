#include <iostream>

#include "CYWebParser.h"

int main(int argc, char** argv)
{
    CYLevel* cyLevel = CYWebParser::loadFileFromWebsite(145505);

    delete cyLevel;
    return 1;
}
