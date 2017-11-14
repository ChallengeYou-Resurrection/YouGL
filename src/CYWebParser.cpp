#include "CYWebParser.h"

// Loads the code from an old parser
CYLevel* loadFile(const std::string& levelCode)
{
    // LEVEL STRUCTURE
    // Old format using Adobe Director's default save file parser
    CYLevel* cyLevel = new CYLevel;

    std::smatch match_groups;
    std::ssub_match sub_match;

    // LEVEL HEADER
    // #name, #levels, #version, #creator
    // Groups: 1 = Name, 2 = Levels, 3 = Version, 4 = Creator
    // Tested with versions 3.68, 3.45, 3.84, 2.13
    std::regex  reg_header("#name: \"([^\"]+)\", #levels: (\\d+), #version: ([^,]+), #creator: \"([^\"]+)\"");
    std::smatch sm_header;

    if (std::regex_search(levelCode, sm_header, reg_header))
    {
        sub_match = sm_header[1];
        cyLevel->m_header.name = sub_match.str();

        sub_match = sm_header[2];
        cyLevel->m_header.levels = std::stoi(sub_match.str());

        sub_match = sm_header[3];
        cyLevel->m_header.version = std::stof(sub_match.str());

        sub_match = sm_header[4];
        cyLevel->m_header.author = sub_match.str();

    } else {
        std::cout << "WEBLOADER ERROR: Could not match header" << std::endl;
        return nullptr;
    }

    // DEBUG
    std::cout << "Name: "  << cyLevel->m_header.name << std::endl;
    std::cout << "Levels: " << cyLevel->m_header.levels << std::endl;
    std::cout << "Version: " << cyLevel->m_header.version << std::endl;
    std::cout << "Author: " << cyLevel->m_header.author << std::endl;

    // Return pointer to CYLevel
    return cyLevel;
}

CYLevel* CYWebParser::loadFileFromWebsite(int gameNumber)
{
    std::cout << "Loading Game #" << gameNumber << std::endl;

    // Setup connection
    sf::Http http;
    http.setHost("http://www.challengeyou.com/");
    std::cout << "Initialising connection to www.challengeyou.com" << std::endl;

    // Setup request
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    std::string uri = "ChallengeFiles/Maze/Maze" + std::to_string(gameNumber);
    request.setUri(uri);
    std::cout << "Sending request to game number #" << gameNumber << std::endl;

    // Send GET Request
    sf::Http::Response response = http.sendRequest(request);

    // Check if it's a success (200)
    if (response.getStatus() != 200)
    {
        std::cout << "FAILED, exited with status: " << response.getStatus() << std::endl;
        return nullptr;

    } else {
        std::cout << "Loading... \n"  << std::endl;
    }

    return loadFile(response.getBody());
}
