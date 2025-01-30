#include "FileList.h"
#include <iostream>

void FileList::add(fs::path path ,std::string fileName, bool isDirectory)
{
    records.emplace_back(path, fileName, isDirectory);
}

const FileRecord& FileList::getCurrentElement() const
{
    return records[currentIndex];
}

const FileRecord& FileList::getRecord(size_t index) const
{
        return records[index];
}

size_t FileList::getcurrentIndex() const
{
    return currentIndex;
}

void FileList::next()
{
    if(currentIndex < records.size() - 1)
        currentIndex++;
}

void FileList::previous()
{
    if(currentIndex > 0)
        currentIndex--;
}

size_t FileList::size() const
{
    return records.size();
}

void FileList::clear()
{
    records.clear();
    currentIndex = 0;
}
