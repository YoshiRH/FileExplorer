#pragma once

#include "../FileList/FileList.h"
#include <string>

namespace FileExplorer {
void loadDirectory(const std::string& filePath, FileList& fileList, bool Drives = false); // Load files from certain directory (filePath) to our list (fileList)
void loadDrives(FileList& fileList);
void displayDirectory(const FileList& fileList);

void openFile(const std::string& filePath);
void createFile(const std::string& filePath);
void deleteFile(const std::string& filePath);
void createDirectory(const std::string& filePath);

void displayHelp();
void displayControls();
void clearScreen();
}