#include "HandleInput.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void handleInput(std::string& currentPath, FileList& fileList, char key)
{

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
                    currentPath = fs::path(currentPath).parent_path().string();
                } else if(selectedFile.isDirectory) {
                    if(currentPath == "/")
                        currentPath += selectedFile.fileName;
                    else
                        currentPath += "/" + selectedFile.fileName;
                } else {
                    FileExplorer::openFile(currentPath + "/" + selectedFile.fileName);
                }

                FileExplorer::loadDirectory(currentPath, fileList);
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Couldn't open the dir: " << e.what() << '\n';
                std::cin.get();
            }
        }
}