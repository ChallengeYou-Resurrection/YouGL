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
    std::regex reg_header("#name: \"([^\"]+)\", #levels: (\\d+), #version: ([^,]+), #creator: \"([^\"]+)\"");

    if (std::regex_search(levelCode, match_groups, reg_header))
    {
        sub_match = match_groups[1];
        cyLevel->m_header.name = sub_match.str();

        sub_match = match_groups[2];
        cyLevel->m_header.levels = std::stoi(sub_match.str());

        sub_match = match_groups[3];
        cyLevel->m_header.version = std::stof(sub_match.str());

        sub_match = match_groups[4];
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

    // GAME GEOMETRY
    // WALLS
    // [Start_X, Start_Y, Displacement_X, Displacement_Y, [Texture1, Texture2, Z_Index], Level]
    // Tested with versions 2.13, 3.12, 3.34, 3.59, 3.68, 3.84
    // TODO: Are there walls with displacement in the decimal direction? (If so please msg me)
    std::regex reg_walls("\\[(-?\\d+), (-?\\d+), (-?\\d+), (-?\\d+), \\[(c[^\\)]*\\))?(\\d+)?, (c[^\\)]*\\))?(\\d+)?]?, (\\d+)],? ?(\\d+)?");

    std::string wall_code = levelCode;
    int wall_id = 0;
    while (std::regex_search(wall_code, match_groups, reg_walls))
    {
        std::cout << "Wall ID: " << wall_id << std::endl;

        sub_match = match_groups[1];
        std::cout << "Start_X: " << sub_match.str() << std::endl;

        sub_match = match_groups[2];
        std::cout << "Start_Y: " << sub_match.str() << std::endl;

        sub_match = match_groups[3];
        std::cout << "Displacement_X: " << sub_match.str() << std::endl;

        sub_match = match_groups[4];
        std::cout << "Displacement_Y: " << sub_match.str() << std::endl;

        wall_id++;
        wall_code = match_groups.suffix();

        std::cout << "------------------" << std::endl;
    }

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
