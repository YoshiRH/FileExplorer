#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// Wrapper class for a file
class FileRecord
{
public:
    std::string fileName;
    fs::path path;
    bool isDirectory;

    FileRecord(fs::path path, std::string& fileName, bool isDirectory) 
    : path(path), fileName(fileName), isDirectory(isDirectory) {}
};
