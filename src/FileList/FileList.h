#pragma once

#include "../FileRecord/FileRecord.h"
#include <vector>

class FileList
{
private:
    std::vector<FileRecord> records;
    size_t currentIndex {0}; // Current element

public:
    void add(const std::string& fileName, bool isDirectory);
    const FileRecord getCurrentElement() const;
    void next();
    void previous();
    size_t size() const;
    void clear();
};
