#pragma once

#include "../FileRecord/FileRecord.h"
#include <vector>


// Class to hold files in certain filePath
class FileList
{
private:
    std::vector<FileRecord> records; // Files in certain 
    size_t currentIndex {0}; // Current element

public:
    void add(std::string fileName, bool isDirectory);
    const FileRecord& getCurrentElement() const;
    const FileRecord& getRecord(size_t index) const;
    size_t getcurrentIndex() const;
    void next();
    void previous();
    size_t size() const;
    void clear();
};
