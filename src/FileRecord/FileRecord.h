#pragma once

#include <string>


// Wrapper class for a file
class FileRecord
{
public:
    std::string fileName;
    bool isDirectory;

    FileRecord(std::string& fileName, bool isDirectory) 
    : fileName(fileName), isDirectory(isDirectory) {}
};
