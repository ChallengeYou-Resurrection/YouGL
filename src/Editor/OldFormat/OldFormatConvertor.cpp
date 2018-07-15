#include "OldFormatUtil.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "../Util/FileUtil.h"

namespace fs = std::experimental::filesystem;

namespace OldFormat {
    namespace {
        void serializeToBinaryFile(std::string& dataBuffer, const fs::path& newFilePath)
        {
            auto table = getObjectTable(dataBuffer);
            auto header = extractHeader(dataBuffer);
			auto walls = std::vector<Wall>();//extractWalls(table["walls"]);

            std::ofstream outFile(newFilePath, std::ios::binary);
            cereal::BinaryOutputArchive archive(outFile);
            
            archive(header, walls);
        }
    }

    void massConvertFilesBinaryFormat()
    {
        auto getNewFilePath = [](const fs::directory_entry& directoryEntry) {
            auto fName = directoryEntry.path().filename().string();
            fName.pop_back(); fName.pop_back();
            return fs::current_path() / "cy_files/binary/" / (fName + "bcy");
        };

        fs::path temp;
        int i = 0;
        std::string buffer;
        for (const auto& entry : fs::directory_iterator(fs::current_path() / "cy_files/old/")) {
            buffer = *getFileContent(entry.path().string());
            auto newPath = getNewFilePath(entry);
            serializeToBinaryFile(buffer, newPath);

            if (++i > 100) break;
            /*
            std::ifstream inFile(temp);
            cereal::BinaryInputArchive archive(inFile);
            
            LevelHeader header;
            std::vector<Wall> walls;
            u32 version;
            archive(version);
            archive(header, walls);
            std::cout << "AFTER: " << header.gameAuthor << " " << header.gameName << " " << header.floorCount << "\n";
            */
        }
        std::cout << "\n Please press enter to continue\n";
        std::cin.ignore();
    }
}
