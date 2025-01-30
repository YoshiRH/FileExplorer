#pragma once

#include "../FileRecord/FileRecord.h"
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;


// Class to hold files in certain filePath
class FileList
{
private:
    std::vector<FileRecord> records; // Files in certain 
    size_t currentIndex {0}; // Current element

public:
    // Add path with fileName to fileList
    void add(fs::path path, std::string fileName, bool isDirectory);

    // Return current element (currentIndex)
    const FileRecord& getCurrentElement() const;

    // Return element with passed index
    const FileRecord& getRecord(size_t index) const;

    
    void next();
    void previous();
    void clear();
    
    size_t getcurrentIndex() const;
    size_t size() const;
};
