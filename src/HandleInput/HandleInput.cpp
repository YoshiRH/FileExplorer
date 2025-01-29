#include "HandleInput.h"
#include "../FileSystemException/FileSystemException.h"
#include <filesystem>

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
        case 'f':
            FileExplorer::createFile(currentPath);
            break;
        case 'z':
            FileExplorer::deleteFile(currentPath + "/" + fileList.getCurrentElement().fileName);
            break;
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
                currentPath = currentPath.empty() ? 
                    currentPath += selectedFile.fileName : currentPath += "/" + selectedFile.fileName;
            } else {
                FileExplorer::openFile(currentPath + "/" + selectedFile.fileName);
                return;
            }
            break;
        }
        default:
            return;
        }
        reloadDirectory(currentPath, fileList, isDrives);
}


