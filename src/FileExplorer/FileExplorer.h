#pragma once

#include "../FileList/FileList.h"
#include "../FileSystemException/FileSystemException.h"
#include <string>

namespace FileExplorer {
// Load files from a directory into fileList
void loadDirectory(const fs::path& filePath, FileList& fileList, bool Drives = false); // Load files from certain directory (filePath) to our list (fileList)

// Load drives from PC into the fileList
void loadDrives(FileList& fileList);

// Print out content of current directory
void displayDirectory(const FileList& fileList);

void openFile(const fs::path& filePath);
void createFile(const fs::path& filePath, const FileList& fileList);
void deleteFile(const fs::path& filePath);
void createDirectory(const fs::path& filePath);
void searchForFile(const fs::path& currentPath, const std::string& query, FileList& fileList);
void renameFile(const FileRecord& file, const std::string& newFileName);
void showFileProperties(const fs::path& filePath);
bool ConditionFindSameFile(const FileList& fileList, const std::string& fileName);

uintmax_t getFolderSize(const fs::path& folderPath);

void displayHelp();
void displayControls();
void clearScreen();
}