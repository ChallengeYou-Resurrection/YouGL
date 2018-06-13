#include "CYJsonParser.h"

// Loads code using the Json parser
CYLevel loadJsonFile(const std::string& levelCode)
{
	// Initialize a CY level
	CYLevel cyLevel;

	// Load json file
	json jLevel;
	jLevel = json::parse(levelCode);

	// Get header information
	cyLevel.m_header.name	 = jLevel["NAME"];
	cyLevel.m_header.levels  = jLevel["LEVELS"];
	cyLevel.m_header.version = jLevel["VERSION"];
	cyLevel.m_header.author  = jLevel["AUTHOR"];
	 
	// DEBUG
	std::cout << "Name: " << cyLevel.m_header.name << '\n';
	std::cout << "Levels: " << cyLevel.m_header.levels << '\n';
	std::cout << "Version: " << cyLevel.m_header.version << '\n';
	std::cout << "Author: " << cyLevel.m_header.author << std::endl;

	// GAME GEOMETRY
	for (auto& wall : jLevel["WALLS"])
	{
		cyLevel.addWall(wall);
	}

	// Build all geometry
	//cyLevel.buildGeometry();

	return cyLevel;
}

CYLevel CYJsonParser::loadFileFromDisk(const std::string& filePath)
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
	return loadJsonFile(std::move(levelCode));
}
