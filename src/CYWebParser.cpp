#include "CYWebParser.h"

// Loads the code from an old parser
CYLevel loadFile(const std::string& levelCode)
{
    // LEVEL STRUCTURE
    // Old format using Adobe Director's default save file parser
    CYLevel cyLevel;
    std::map<std::string, std::string> cyTable = classifiedLevelCode(levelCode);

    std::smatch matchGroups;
    std::ssub_match subMatch;

    // LEVEL HEADER
    // #name, #levels, #version, #creator
    // Groups: 1 = Name, 2 = Levels, 3 = Version, 4 = Creator
    // Tested with versions 3.68, 3.45, 3.84, 2.13
    std::regex regexHeader("#name: \"([^\"]+)\", #levels: (\\d+), #version: ([^,]+), #creator: \"([^\"]+)\"");

    if (std::regex_search(levelCode, matchGroups, regexHeader))
    {
        subMatch = matchGroups[1];
        cyLevel.m_header.name = subMatch.str();

        subMatch = matchGroups[2];
        cyLevel.m_header.levels = std::stoi(subMatch.str());

        subMatch = matchGroups[3];
        cyLevel.m_header.version = std::stof(subMatch.str());

        subMatch = matchGroups[4];
        cyLevel.m_header.author = subMatch.str();

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
	std::regex reg_walls("\\[(-?\\d+), (-?\\d+), (-?\\d+), (-?\\d+), \\[(c[^\\)]*\\))?(\\d+)?, (c[^\\)]*\\))?(\\d+)?\\]?, (\\d+)\\],? ?(\\d+)?");

    int wall_id = 0;
    while (std::regex_search(wallCode, matchGroups, reg_walls))
    {
        cyLevel.addWall(matchGroups);

        wall_id++;
        wallCode = matchGroups.suffix();
	}

    // PLATFORMS
    // V2.13 = [X_Pos, Y_Pos, [Texture], Level]
    // V3.06-3.27 = [X_Pos, Y_Pos, [Size, Texture], Level]
    // V3.37+ = [X_Pos, Y_Pos, [Size, Texture, Z_Index], Level]
    // Tested on Version 2.13, 3.06, 3.09, 3.13, 3.27. 3.37, 3.52, 3.68
    std::string platCode = cyTable.at("Plat");
	std::regex reg_plats("\\[\\[([\\d\\.]+), ([\\d\\.]+)\\], \\[(\\d+),? ?(c[^\\)]*\\))?(\\d+)?,? ?(\\d+)?\\], (\\d+)");

    while (std::regex_search(platCode, matchGroups, reg_plats))
    {
        cyLevel.addPlat(matchGroups);

        platCode = matchGroups.suffix();
        //std::cout << "------------------" << std::endl;
    }

    std::map<std::string, std::string> classes = classifiedLevelCode(levelCode);

    cyLevel.buildGeometry();
    std::cout << "done" << std::endl;

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
        if ((levelCode.at(charPos) == '#' && !isInString) || charPos == levelCode.length() - 3)
        {
            if (charPos != 1)
            {
                std::size_t nameStart = levelCode.find(":", groupStart);
                std::string name = levelCode.substr(groupStart + 1, nameStart - groupStart - 1);

                std::string contents = levelCode.substr(nameStart + 2, charPos-nameStart - 4);

                cyTable.emplace(name, contents);
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

CYLevel CYWebParser::loadFileFromDisk(const std::string& filePath)
{
	std::cout << "Loading " << filePath << '\n';

	// Setup string buffers for reading file
	std::string levelCode;
	std::ifstream levelCodeBuffer;
	levelCodeBuffer.exceptions(std::ifstream::badbit);

	// Open the file
	try
	{
		// Open
		levelCodeBuffer.open(filePath);

		// Read into a string stream
		std::stringstream levelSS;
		levelSS << levelCodeBuffer.rdbuf();

		// Convert the stream stream into a string we can use & close the buffer
		levelCode = levelSS.str();
		levelCodeBuffer.close();

	}
	// Error reading file
	catch (std::ifstream::failure e) {
		std::cout << "Could not load file " << filePath << std::endl;
	}

	// Load the level & return
	return loadFile(levelCode);
}