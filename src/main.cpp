#include <iostream>

#include "CYWebParser.h"

int main(int argc, char** argv)
{
    CYLevel* cyLevel = CYWebParser::loadFileFromWebsite(10038);

    delete cyLevel;
    return 1;
}
