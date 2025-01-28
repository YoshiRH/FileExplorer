#include "HandleInput.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
constexpr int ROOT_SIZE_PATH {3};

void handleInput(std::string& currentPath, FileList& fileList, char key)
{
        bool isDrives {false};

        if(key == 'd') {
            FileExplorer::createDirectory(currentPath);
            FileExplorer::loadDirectory(currentPath, fileList);
            return;
        }
        else if(key == 'f') {
            FileExplorer::createFile(currentPath);
            FileExplorer::loadDirectory(currentPath, fileList);
            return;
        }
        else if(key == 'z') {
            FileExplorer::deleteFile(currentPath + "/" + fileList.getCurrentElement().fileName);
            FileExplorer::loadDirectory(currentPath, fileList);
            return;
        }

        if (key == 72) {
            fileList.previous();
        } else if (key == 80) {
            fileList.next();
        } else if(key == 13) {
            const FileRecord& selectedFile = fileList.getCurrentElement();

            try {
                if(selectedFile.fileName == "..") {
                    if(currentPath.length() == ROOT_SIZE_PATH) {
                        isDrives = true;
                        currentPath.clear();
                    } else {
                        currentPath = fs::path(currentPath).parent_path().string();
                    }
                } else if(selectedFile.isDirectory) {
                    if(currentPath.empty())
                        currentPath += selectedFile.fileName;
                    else
                        currentPath += "/" + selectedFile.fileName;
                } else {
                    FileExplorer::openFile(currentPath + "/" + selectedFile.fileName);
                }

                FileExplorer::loadDirectory(currentPath, fileList, isDrives);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Couldn't open the dir: " << e.what() << '\n';
                std::cin.get();
            }
        }
}