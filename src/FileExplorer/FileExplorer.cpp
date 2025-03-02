#include "FileExplorer.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#ifdef _WIN32
    #include <windows.h>
#endif


namespace fs = std::filesystem;

// Load all available drives on Windows or the root dir on other platforms
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
            fileList.add(std::string(1, drive) + ":/" ,std::string(1, drive) + ":/", true);
        }

        // Move bit one position to right -> move to next disk (A-Z) 
        driveMask >>= 1;
    }
#else
    // Just add root directory if it's not Windows
    fileList.add("/", "/", true);
#endif
}

// Load all files/dirs in certain directory to our fileList
void FileExplorer::loadDirectory(const fs::path &filePath, FileList &fileList, bool Drives)
{
    fileList.clear();

    if(Drives) {
        loadDrives(fileList);
        return;
    }

    fileList.add(filePath.parent_path(), "..", true);

    // Load every file in directory to our list
    try{
        for(auto& file : fs::directory_iterator(filePath)) {
            fileList.add(file.path() ,file.path().filename().string(), file.is_directory());
        }
    } catch (fs::filesystem_error& e) {
        throw FileSystemException("Couldn't load the directory: " + filePath.string());
    }
}

// Display all files/dirs in certain directory
void FileExplorer::displayDirectory(const FileList &fileList)
{
    clearScreen();
    std::cout << '\n';

    for(size_t i=0; i<fileList.size(); i++) {
        const FileRecord& record = fileList.getRecord(i);

        std::cout << (i == fileList.getcurrentIndex() ? "\033[1;32m> " : " ");
        std::cout << (record.isDirectory ? "\033[1;34m[DIR] " : "\033[1;33m[FILE] ") << record.fileName << "\033[0m" << '\n';
    }

    displayControls();
}

void FileExplorer::openFile(const fs::path& filePath)
{
    std::ifstream file(filePath);

    if(!file) {
        throw FileSystemException("Couldn't open the file" + filePath.string());
    }

    clearScreen();
    std::string line;
    while(std::getline(file, line)) {
        std::cout << line << '\n';
    }

    std::cout << "\nPress any key to close the file...\n";
    std::cin.get();
}

void FileExplorer::createFile(const fs::path& filePath, const FileList& fileList)
{
    clearScreen();

    std::string fileName{};
    std::string msg{};

    std::cout << "Enter the name of the file: ";
    std::getline(std::cin, fileName);
    std::cout << "\n\nEnter the msg:";
    std::getline(std::cin, msg);

    bool replaceFile = ConditionFindSameFile(fileList, fileName);

    if(replaceFile) {
        std::ofstream file(filePath.string() + "/" + fileName + ".txt");
    
        if(file.is_open()) {
            file << msg;
            file.close();
        } else {
            throw FileSystemException("Couldn't create the file: " + fileName);
        }
    } 
}

bool FileExplorer::ConditionFindSameFile(const FileList& fileList, const std::string& fileName)
{
    for(auto i=0; i<fileList.size(); i++) {
        if(fileList.getRecord(i).fileName == (fileName + ".txt")) {
            std::cout << "Current directory contain a file with the same name\n";
            std::cout << "Do you want to continue and override existing file? [y - yes, n - no]: ";

            char choice{};
            std::cin >> choice;

            if(choice == 'y')
                return true;
            else
                return false;
        }
    }
    
    return true;
}

void FileExplorer::deleteFile(const fs::path& filePath)
{
    clearScreen();

    char choice{};
    std::cout << "Do you want to delete this file? [y - yes, n - no]: ";
    std::cin >> choice;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(choice == 'y') {
        std::uintmax_t amount {};
        try{
            amount = fs::remove_all(filePath);
        } catch (fs::filesystem_error& e) {
            throw FileSystemException("Couldn't delete the file: " + filePath.filename().string());
        }
        
        std::cout << "Deleted " << amount << " files in total.\n\nPress any key to continue...\n";
        std::cin.get();
    }
}

void FileExplorer::createDirectory(const fs::path& filePath)
{
    clearScreen();

    std::string dirName{};
    std::cout << "\nEnter the name of the directory: ";
    std::getline(std::cin, dirName);

    if(!fs::exists(dirName)) {
        try{
            fs::create_directory(filePath.string() + "/" + dirName);
        } catch (const fs::filesystem_error& e) {
            throw FileSystemException("Couldn't create the directory: " + dirName);
        }
    } else {
        std::cout << "Can't create directory, dir with the same name already exist\n";
        std::cout << "Click enter to continue...\n";
        std::cin.get();
    }
}

void FileExplorer::searchForFile(const fs::path& currentPath, const std::string &query, FileList &fileList)
{
    bool isFirst {true};
    std::cout << "Looking for matching files, it may take a while...";

    // Go through all the files in directory and add to list files that match the query
    for(const auto& entry : fs::recursive_directory_iterator(currentPath)) {
        if(entry.path().filename().string().find(query) != std::string::npos) {
            if(isFirst){
                fileList.clear();
                fileList.add(fs::path(currentPath), "GO BACK", true);
                isFirst = false;
                fileList.add(entry.path() ,entry.path().filename().string(), entry.is_directory());
            }
        }
    }

    if(isFirst) {
        std::cout << "Couldn't find the file: " << query << '\n';
        std::cout << "Click Enter to continue... \n";
        std::cin.get();
    }
}

void FileExplorer::renameFile(const FileRecord& file, const std::string &newFileName)
{
    fs::path newPath{};

    if (!file.isDirectory) {
        std::string fileType = file.fileName.substr(file.fileName.find_last_of('.'));
        newPath = file.path.parent_path() / (newFileName + fileType);
    } else {
        newPath = file.path.parent_path() / newFileName;
    }

    try{
        fs::rename(file.path, newPath);
    } catch (const fs::filesystem_error& e) {
        std::cout << "Couldn't change the file name from: " << file.fileName << " to " << newFileName << '\n';
        std::cout << "Reason: " << e.what() << '\n';
        std::cin.get();
    }
}

void FileExplorer::showFileProperties(const fs::path &filePath)
{
    clearScreen();
    try {
        // Basic file info
        std::cout << "File: " << filePath.filename().string() << '\n';
        std::cout << "File path: " << filePath.string() << '\n';
        std::cout << "_______________________________________\n\n";

        // Check the file type
        if(fs::is_directory(filePath)) {
            std::cout << "Type: Directory\n";
            std::cout << "Contains: " << std::distance(fs::directory_iterator(filePath), fs::directory_iterator{}) << " items.\n";
            uintmax_t directorySize = getFolderSize(filePath);
            std::cout << "Size: " << directorySize << " bytes\n";
        } else if (fs::is_regular_file(filePath)) {
            std::cout << "Type: File\n";
            std::cout << "Size: " << fs::file_size(filePath) << " bytes\n";
            std::cout << "Empty: " << (fs::is_empty(filePath) ? "Yes\n" : "No\n");
        } else {
            std::cout << "Type: Other\n";
        }

        // Convert and show time of last modification
        auto ftime = fs::last_write_time(filePath);
        auto convertedFTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
            ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
            );
        std::time_t cFTime = std::chrono::system_clock::to_time_t(convertedFTime);
        std::cout << "\nLast modified: " << std::put_time(std::localtime(&cFTime), "%Y-%m-%d %H:%M:%S") << '\n';
        
        // Convert and show file permissions
        fs::perms permissions = fs::status(filePath).permissions();
        std::cout << "Permissions: ";
        std::cout << ((permissions & fs::perms::owner_read) != fs::perms::none ? "r" : "-");
        std::cout << ((permissions & fs::perms::owner_write) != fs::perms::none ? "w" : "-");
        std::cout << ((permissions & fs::perms::owner_exec) != fs::perms::none ? "x\n" : "-\n");
        
        std::cout << "\n\nTo exit click on any key...\n";
        std::cin.get();
    } catch (const fs::filesystem_error& e) {
        throw FileSystemException("Couldn't load the file information: " + filePath.filename().string());
    }
}

uintmax_t FileExplorer::getFolderSize(const fs::path &folderPath)
{
    uintmax_t size {0};

    // Sum up size of all files in directory
    try {
        for(const auto& entry : fs::recursive_directory_iterator(folderPath)) {
            if(fs::is_regular_file(entry)) {
                size += fs::file_size(entry);
            }
        }
    } catch (const fs::filesystem_error& e) {
        throw FileSystemException("Couldn't calculate the directory size");
    }

    return size;
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
    std::cout << "Z          - Create .txt file\n";
    std::cout << "X          - Delete file/directory\n";
    std::cout << "F          - Search for file\n";
    std::cout << "R          - Rename file\n";
    std::cout << "I          - Show file info\n";
    std::cout << "Q          - Exit\n";
    std::cout << "\nPress any key to continue...\n";

    std::cin.get();
}

void FileExplorer::displayControls()
{
    std::cout << "\n[D - Create dir] [Z - Create .txt] [X - Delete] [F - Find]\n";
    std::cout << "[R - Rename] [I - Info]\n\n";
}