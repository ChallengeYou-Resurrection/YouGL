#include "CYWebParser.h"

// Loads the code from an old parser
CYLevel loadFile(const std::string& levelCode)
{
    // LEVEL STRUCTURE
    // Old format using Adobe Director's default save file parser
    CYLevel cyLevel;
    std::map<std::string, std::string> cyTable = classifiedLevelCode(levelCode);

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
        cyLevel.m_header.name = sub_match.str();

        sub_match = match_groups[2];
        cyLevel.m_header.levels = std::stoi(sub_match.str());

        sub_match = match_groups[3];
        cyLevel.m_header.version = std::stof(sub_match.str());

        sub_match = match_groups[4];
        cyLevel.m_header.author = sub_match.str();

    } else {
        std::cout << "WEBLOADER ERROR: Could not match header" << std::endl;
        return {};
    }

    // DEBUG
    std::cout << "Name: "  << cyLevel.m_header.name << '\n';
    std::cout << "Levels: " << cyLevel.m_header.levels << '\n';
    std::cout << "Version: " << cyLevel.m_header.version << '\n';
    std::cout << "Author: " << cyLevel.m_header.author << std::endl;

    // GAME GEOMETRY
    // WALLS
    // [Start_X, Start_Y, Displacement_X, Displacement_Y, [Texture1, Texture2, Z_Index], Level]
    // Tested with versions 2.13, 3.12, 3.34, 3.59, 3.68, 3.84
    // TODO: Are there walls with displacement in the decimal direction? (If so please msg me)
    std::string wallCode = cyTable.at("walls");
#ifdef _MSC_VER //If the compiler is MSVC
    std::regex reg_walls("\\[(-?\\d+), (-?\\d+), (-?\\d+), (-?\\d+), \\[(c[^\\)]*\\))?(\\d+)?, (c[^\\)]*\\))?(\\d+)?]?, (\\d+)],? ?(\\d+)?");
#else 
    std::regex reg_walls("\\[(-?\\d+), (-?\\d+), (-?\\d+), (-?\\d+), \\[(c[^\\)]*\\))?(\\d+)?, (c[^\\)]*\\))?(\\d+)?]?, (\\d+)],? ?(\\d+)?");
#endif

    int wall_id = 0;
    while (std::regex_search(wallCode, match_groups, reg_walls))
    {
        std::cout << "Wall ID: " << wall_id << '\n';

        cyLevel.addWall(match_groups);

        wall_id++;
        wallCode = match_groups.suffix();

        std::cout << "------------------" << std::endl;
    }

    // PLATFORMS
    // V2.13 = [X_Pos, Y_Pos, [Texture], Level]
    // V3.06-3.27 = [X_Pos, Y_Pos, [Size, Texture], Level]
    // V3.37+ = [X_Pos, Y_Pos, [Size, Texture, Z_Index], Level]
    // Tested on Version 2.13, 3.06, 3.09, 3.13, 3.27. 3.37, 3.52, 3.68
    std::string platCode = cyTable.at("Plat");
    std::regex reg_plats("\\[\\[([\\d\\.]+), ([\\d\\.]+)], \\[(\\d+),? ?(c[^\\)]*\\))?(\\d+)?,? ?(\\d+)?], (\\d+)");

    //std::regex_search(levelCode, match_groups, reg_platCode);
    //td::string plat_code = match_groups[1].str();

    while (std::regex_search(platCode, match_groups, reg_plats))
    {
        cyLevel.addPlat(match_groups);

        platCode = match_groups.suffix();
        std::cout << "------------------" << std::endl;
    }

    std::map<std::string, std::string> classes = classifiedLevelCode(levelCode);

    return cyLevel;
}

std::map<std::string, std::string> classifiedLevelCode(const std::string& levelCode)
{
    std::map<std::string, std::string> cyTable;

    int charPos = 0;
    int groupStart = 0;
    bool isInString = false;

    // length 6, at(5)
    while ((unsigned)charPos < (levelCode.length() - 2))
    {
        if (levelCode.at(charPos) == '"')
            isInString = !isInString;

        // If # and not in a string
        if ((levelCode.at(charPos) == '#' && !isInString) || charPos == levelCode.length()-3)
        {
            if (charPos != 1)
            {
                std::size_t name_start = levelCode.find(":", groupStart);
                std::string name = levelCode.substr(groupStart+1, name_start-groupStart-1);

                std::string contents = levelCode.substr(name_start+2, charPos-name_start-4);

                cyTable.emplace(std::make_pair(name, contents));
                //std::cout << name << " ;) \n" << contents << "\n";
            }

            groupStart = charPos;
        }

        charPos++;
    }

    return cyTable;
}

CYLevel CYWebParser::loadFileFromWebsite(int gameNumber)
{
    std::cout << "Loading Game #" << gameNumber << '\n';

    // Setup connection
    sf::Http http;
    http.setHost("http://www.challengeyou.com/");
    std::cout << "Initialising connection to www.challengeyou.com" << '\n';

    // Setup request
    sf::Http::Request request;
    request.setMethod(sf::Http::Request::Get);
    std::string uri = "ChallengeFiles/Maze/Maze" + std::to_string(gameNumber);
    request.setUri(uri);
    std::cout << "Sending request to game number #" << gameNumber << '\n';

    // Send GET Request
    sf::Http::Response response = http.sendRequest(request);

    // Check if it's a success (200)
    if (response.getStatus() != 200)
    {
        std::cout << "FAILED, exited with status: " << response.getStatus() << '\n';
        return {};

    } else {
        std::cout << "Loading... \n"  << std::endl;
    }

    return loadFile(response.getBody());
}
