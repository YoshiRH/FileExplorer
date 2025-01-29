#pragma once

#include <stdexcept>
#include <string>

// Additional class to handle all of exceptions in the same way
class FileSystemException : public std::runtime_error {
public: 
    explicit FileSystemException(const std::string& message)
    : std::runtime_error("File System Error: " + message) {};
};