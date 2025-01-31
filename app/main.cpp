#include "../src/FileExplorer/FileExplorer.h"
#include "../src/HandleInput/HandleInput.h"
#include <iostream>
#include <filesystem>
#include <conio.h>

namespace fs = std::filesystem;

int main() {
    FileExplorer::displayHelp();

    fs::path currentPath;
    FileList fileList;

    FileExplorer::loadDirectory(currentPath, fileList, true);

    while(true) {
        FileExplorer::displayDirectory(fileList);

        char key = _getch();
        
        if(key == 'q')
            break;
        
        handleInput(currentPath, fileList, key);
    }

    return 0;
}