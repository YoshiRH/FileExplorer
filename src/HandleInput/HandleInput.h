#pragma once

#include "../FileExplorer/FileExplorer.h"
#include "../FileList/FileList.h"
#include "../FileRecord/FileRecord.h"
#include "../FileSystemException/FileSystemException.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace HandleKeys{
    constexpr char KEY_UP = 72;
    constexpr char KEY_DOWN = 80;
    constexpr char KEY_ENTER = 13;
} 

// Main function to decide what to do depending on entered key by user
void handleInput(fs::path& currentPath, FileList& fileList, char key);

void reloadDirectory(const fs::path& currentPath, FileList& fileList, bool isDrives);