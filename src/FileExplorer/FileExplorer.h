#pragma once

#include "../FileList/FileList.h"
#include "../FileSystemException/FileSystemException.h"
#include <string>

namespace FileExplorer {
// Load files from a directory into fileList
void loadDirectory(const std::string& filePath, FileList& fileList, bool Drives = false); // Load files from certain directory (filePath) to our list (fileList)

// Load drives from PC into the fileList
void loadDrives(FileList& fileList);

// Print out content of current directory
void displayDirectory(const FileList& fileList);

void openFile(const fs::path& filePath);
void createFile(const std::string& filePath);
void deleteFile(const std::string& filePath);
void createDirectory(const std::string& filePath);
void searchForFile(const std::string& currentPath, const std::string& query, FileList& fileList);

void displayHelp();
void displayControls();
void clearScreen();
}