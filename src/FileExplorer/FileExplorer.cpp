#include "FileExplorer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <windows.h>

namespace fs = std::filesystem;

void FileExplorer::loadDrives(FileList& fileList)
{
#ifdef _WIN32
    // Get bitMask of available disks in system
    DWORD driveMask = GetLogicalDrives(); 

    if(driveMask == 0) {
        std::cerr << "Couldn't load any drives...\n";
        std::cin.get();
        return;
    }

    for(char drive = 'A'; drive <= 'Z'; drive++) {
        // If bit is equal to 1, it means that this specific disk (A-Z) is available
        if(driveMask & 1) {
            fileList.add(std::string(1, drive) + ":/", true);
        }

        // Move bit one position to right -> move to next disk (A-Z) 
        driveMask >>= 1;
    }
#else
    // Just add root directory if it's not Windows
    fileList.add("/", true);
#endif
}

void FileExplorer::loadDirectory(const std::string &filePath, FileList &fileList, bool Drives)
{
    fileList.clear();

    if(Drives) {
        loadDrives(fileList);
        return;
    }

    fs::path path(filePath);
    fileList.add("..", true);

    // Load every file in directory to our list
    try{
        for(auto& file : fs::directory_iterator(path)) {
            fileList.add(file.path().filename().string(), file.is_directory());
        }
    } catch (fs::filesystem_error& e) {
        throw FileSystemException("Couldn't load the directory: " + path.string());
    }
}

void FileExplorer::displayDirectory(const FileList &fileList)
{
    clearScreen();
    std::cout << '\n';

    for(size_t i=0; i<fileList.size(); i++) {
        const FileRecord& record = fileList.getRecord(i);

        std::cout << (i == fileList.getcurrentIndex() ? "\033[1;32m> " : " ");
        std::cout << (record.isDirectory ? "[DIR] " : "[FILE] ") << record.fileName << "\033[0m" << '\n';
    }

    displayControls();
}

void FileExplorer::openFile(const std::string &filePath)
{
    fs::path path(filePath);
    std::ifstream file(path);

    if(!file) {
        throw FileSystemException("Couldn't open the file" + path.string());
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

void FileExplorer::createFile(const std::string &filePath)
{
    fs::path path(filePath);
    clearScreen();

    std::string fileName{};
    std::string msg{};

    std::cout << "Enter the name of the file: ";
    std::getline(std::cin, fileName);
    std::cout << "\n\nEnter the msg:";
    std::getline(std::cin, msg);

    std::ofstream file(path.string() + "/" + fileName + ".txt");
    
    if(file.is_open()) {
        file << msg;
        file.close();
    } else {
        throw FileSystemException("Couldn't create the file: " + fileName);
    }
}

void FileExplorer::deleteFile(const std::string &filePath)
{
    fs::path path(filePath);
    clearScreen();

    char choice{};
    std::cout << "Do you want to delete this file? [y - yes, n - no]: ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(choice == 'y') {
        std::uintmax_t amount {};
        try{
            amount = fs::remove_all(path);
        } catch (fs::filesystem_error& e) {
            throw FileSystemException("Couldn't delete the file: " + path.filename().string());
        }
        
        std::cout << "Deleted " << amount << " files in total.\n\nPress any key to continue...\n";
        std::cin.get();
    }
}

void FileExplorer::createDirectory(const std::string &filePath)
{
    fs::path path(filePath);
    clearScreen();

    std::string dirName{};
    std::cout << "\nEnter the name of the directory: ";
    std::getline(std::cin, dirName);

    if(!fs::exists(dirName)) {
        try{
            fs::create_directory(path.string() + "/" + dirName);
        } catch (const fs::filesystem_error& e) {
            throw FileSystemException("Couldn't create the directory: " + dirName);
        }
    }
}

void FileExplorer::clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void FileExplorer::displayHelp()
{
    std::cout << "============= Controls =============\n";
    std::cout << "Arrow UP   - Move to previous element\n";
    std::cout << "Arrow DOWN - Move to next element\n";
    std::cout << "Enter      - Open directory or file\n";
    std::cout << "D          - Create directory \n";
    std::cout << "F          - Create .txt file\n";
    std::cout << "Z          - Delete file/directory\n";
    std::cout << "Q          - Exit\n";
    std::cout << "\nPress any key to continue...\n";

    std::cin.get();
}

void FileExplorer::displayControls()
{
    std::cout << "\n[D - Create dir] [F - Create .txt] [Z - Delete]\n\n";
}