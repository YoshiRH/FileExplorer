#pragma once

#include <string>

class FileRecord
{
public:
    std::string fileName;
    bool isDirectory;

    FileRecord(std::string& fileName, bool isDirectory) 
    : fileName(fileName), isDirectory(isDirectory) {}
};
