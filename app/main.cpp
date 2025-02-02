#include "../src/FileExplorer/FileExplorer.h"
#include "../src/HandleInput/HandleInput.h"
#include <iostream>
#include <filesystem>

#ifdef _WIN32
    #include <conio.h>
#else
    #include <unistd.h>
#endif

namespace fs = std::filesystem;

char getInput();

int main() {
    FileExplorer::displayHelp();

    fs::path currentPath;
    FileList fileList;

    FileExplorer::loadDirectory(currentPath, fileList, true);

    while(true) {
        FileExplorer::displayDirectory(fileList);

        char key = getInput();
        
        if(key == 'q')
            break;
        
        handleInput(currentPath, fileList, key);
    }

    return 0;
}

char getInput()
{
    #ifdef _WIN32
        return _getch();
    #else 
        return getchar();
    #endif
}
