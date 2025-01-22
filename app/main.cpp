#include "../src/FileExplorer/FileExplorer.h"
#include <iostream>
#include <filesystem>
#include <conio.h>

namespace fs = std::filesystem;

int main() {
    FileExplorer::displayHelp();

    std::string currentPath {"."};
    FileList fileList;

    FileExplorer::loadDirectory(currentPath, fileList);

    while(true) {
        FileExplorer::displayDirectory(fileList);

        char key = _getch();
        

        if(key == 'q') {
            break;
        }

        if (key == 72) 
            fileList.previous();
        else if (key == 80) 
            fileList.next();
        else if(key == 13) {
            const FileRecord& selectedFile = fileList.getCurrentElement();

            try {
                if(selectedFile.fileName == "..") {
                    currentPath = fs::path(currentPath).parent_path().string();
                } else if(selectedFile.isDirectory) {
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

    return 0;
}