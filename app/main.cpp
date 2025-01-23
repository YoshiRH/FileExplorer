#include "../src/FileExplorer/FileExplorer.h"
#include "../src/HandleInput/HandleInput.h"
#include <iostream>
#include <filesystem>
#include <conio.h>

namespace fs = std::filesystem;

int main() {
    FileExplorer::displayHelp();

    std::string currentPath {"/"};
    FileList fileList;

    FileExplorer::loadDirectory(currentPath, fileList);

    while(true) {
        FileExplorer::displayDirectory(fileList);

        char key = _getch();
        
        if(key == 'q')
            break;
        
        handleInput(currentPath, fileList, key);
    }

    return 0;
}