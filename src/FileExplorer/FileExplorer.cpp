
#include "FileExplorer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

void FileExplorer::loadDirectory(const std::string &filePath, FileList &fileList)
{
    fileList.clear();

    // Check if there is possibility to move to parent dir
    if(fs::path(filePath) != fs::path("/")) {
        fileList.add("..", true);
    }

    // Load every file in directory to our list
    try{
        for(const auto& file : fs::directory_iterator(filePath)) {
            fileList.add(file.path().filename().string(), file.is_directory());
        }
    } catch (fs::filesystem_error& e) {
        std::cerr << "Couldn't load the directory: " << e.what() << '\n';
    }
}

void FileExplorer::displayDirectory(const FileList &fileList)
{
    clearScreen();

    for(size_t i=0; i<fileList.size(); i++) {
        const FileRecord& record = fileList.getRecord(i);

        if(i == fileList.getcurrentIndex()) {
             std::cout << "\033[1;32m> ";
        } else {
            std::cout << " ";
        }

        std::cout << (record.isDirectory ? "[DIR] " : "[FILE] ") << record.fileName << "\033[0m" << '\n';
    }
}

void FileExplorer::displayHelp()
{
    std::cout << "============= Controls =============\n";
    std::cout << "Arrow UP   - Move to previous element\n";
    std::cout << "Arrow DOWN - Move to next element\n";
    std::cout << "Enter      - Open directory or file\n";
    std::cout << "Q          - Exit\n";
    std::cout << "\nPress any key to continue...\n";

    std::cin.get();
}

void FileExplorer::openFile(const std::string &filePath)
{
    std::ifstream file(filePath);

    if(!file) {
        std::cerr << "Couldn't open the file: " << filePath << '\n';
        std::cin.get();
        return;
    }

    clearScreen();
    std::string line;

    while(std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    std::cout << "\nPress any key to close the file...\n";
    std::cin.get();
}

void FileExplorer::clearScreen()
{
    std::cout << system("cls");
}

