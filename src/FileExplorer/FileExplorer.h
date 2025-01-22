#pragma once

#include "../FileList/FileList.h"
#include <string>

namespace FileExplorer {
void loadDirectory(const std::string& filePath, FileList& fileList); // Load files from certain directory (filePath) to our list (fileList)
void displayDirectory(const FileList& fileList);
void displayHelp();
void openFile(const std::string& filePath);
void clearScreen();
}