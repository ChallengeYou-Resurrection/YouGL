#include "OldFormatUtil.h"

#include <iostream>
#include <SFML/Network/Http.hpp>

namespace OldFormat
{
    std::optional<std::string> loadFromWebsite(int gameNumber)
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

        }
        else {
            std::cout << "Loading... \n" << std::endl;
        }

        return response.getBody();
    }

	// Requires an Apache server setup that behaves just like the CY server
	std::optional<std::string> loadFromLocalhost(int gameNumber)
	{
		std::cout << "Loading Game #" << gameNumber << '\n';

		// Setup connection
		sf::Http http;
		http.setHost("localhost/");
		std::cout << "Initialising connection to localhost" << '\n';

		// Setup request
		sf::Http::Request request;
		request.setMethod(sf::Http::Request::Get);
		std::string uri = "maze.php";// +std::to_string(gameNumber);
		request.setUri(uri);
		std::cout << "Sending request to game number #" << gameNumber << '\n';

		// Send GET Request
		sf::Http::Response response = http.sendRequest(request);

		// Check if it's a success (200)
		if (response.getStatus() != 200)
		{
			std::cout << "FAILED, exited with status: " << response.getStatus() << '\n';
			return {};

		}
		else {
			std::cout << "Loading... \n" << std::endl;
		}

		return response.getBody();
	}

    std::unordered_map<std::string, std::string> getObjectTable(const std::string & levelCode)
    {
        std::unordered_map<std::string, std::string> cyTable;

        int groupStart = 0;
        bool isInString = false;

        // length 6, at(5)
        for (unsigned charPos = 0; charPos < (levelCode.length() - 2); charPos++) {
            if (levelCode.at(charPos) == '"')
                isInString = !isInString;

            // If # and not in a string
            if ((levelCode.at(charPos) == '#' && !isInString) || charPos == levelCode.length() - 3) {
                if (charPos != 1) {
                    std::size_t nameStart = levelCode.find(":", groupStart);
                    std::string name = levelCode.substr(groupStart + 1, nameStart - groupStart - 1);
                    std::string contents = levelCode.substr(nameStart + 2, charPos - nameStart - 4);

                    cyTable.emplace(name, contents);
                }
                groupStart = charPos;
            }
        }
        return cyTable;
    }
}

