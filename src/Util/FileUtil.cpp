#include "FileUtil.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::optional<std::string> getFileContent(const std::string& filePath)
{
    std::ifstream inFile(filePath);
    if (!inFile.is_open())
    {
        std::string error = "Unable to open file: " + filePath + "!";
        return {};
    }

    std::ostringstream stream;
    stream << inFile.rdbuf();
    return stream.str();
}
