#include "HandleInput.h"
#include "../FileSystemException/FileSystemException.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
constexpr int ROOT_SIZE_PATH {3};

void reloadDirectory(const std::string &currentPath, FileList &fileList, bool isDrives) 
{
    try {
        FileExplorer::loadDirectory(currentPath, fileList, isDrives);
    } catch (const fs::filesystem_error& e) {
        throw FileSystemException("Failed to load directory: " + std::string(e.what()));
    }
}

void handleInput(std::string& currentPath, FileList& fileList, char key)
{
        bool isDrives {false};

        switch (key)
        {
        case 'd':
            FileExplorer::createDirectory(currentPath);
            break;
        case 'z':
            FileExplorer::createFile(currentPath);
            break;
        case 'x':
            FileExplorer::deleteFile(currentPath + "/" + fileList.getCurrentElement().fileName);
            break;
        case 'f': 
        {
            std::cout << "Enter the file name which you want to find: ";
            std::string fileName{};
            std::getline(std::cin, fileName);
            FileExplorer::searchForFile(currentPath, fileName, fileList);
            return;  
        }      
        case HandleKeys::KEY_UP:
            fileList.previous();
            return;
        case HandleKeys::KEY_DOWN: 
            fileList.next();
            return;
        case HandleKeys::KEY_ENTER: { 
            const FileRecord& selectedFile = fileList.getCurrentElement();

            if(selectedFile.fileName == "..") {
                if(currentPath.length() == ROOT_SIZE_PATH) {
                    isDrives = true;
                    currentPath.clear();
                } else {
                    currentPath = fs::path(currentPath).parent_path().string();
                }
            } else if(selectedFile.isDirectory) {
                currentPath = selectedFile.path.string();
            } else {
                FileExplorer::openFile(selectedFile.path);
                return;
            }
            break;
        }
        default:
            return;
        }
        reloadDirectory(currentPath, fileList, isDrives);
}


