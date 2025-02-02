#include "HandleInput.h"

constexpr int ROOT_SIZE_PATH {3};

void reloadDirectory(const fs::path& currentPath, FileList &fileList, bool isDrives) 
{
    try {
        FileExplorer::loadDirectory(currentPath, fileList, isDrives);
    } catch (const fs::filesystem_error& e) {
        throw FileSystemException("Failed to load directory: " + std::string(e.what()));
    }
}

void findFile(const fs::path& currentPath, FileList& fileList)
{
    std::cout << "Enter the file name which you want to find: ";
            std::string fileName{};
            std::getline(std::cin, fileName);
            FileExplorer::searchForFile(currentPath, fileName, fileList);
            return;
}

void renameFile(const FileList& fileList)
{
    const FileRecord& selectedFile = fileList.getCurrentElement();
    std::string fileName{};

    std::cout << "Enter new file name: ";
    std::getline(std::cin, fileName);

    FileExplorer::renameFile(selectedFile, fileName);
}

void showFileProperties(const FileList &fileList)
{
    const FileRecord& selectedFile = fileList.getCurrentElement();
    FileExplorer::showFileProperties(selectedFile.path);
}

void handleInput(fs::path& currentPath, FileList& fileList, char key)
{
        bool isDrives {false};

        switch (key)
        {
        case 'd':
            FileExplorer::createDirectory(currentPath);
            break;
        case 'z':
            FileExplorer::createFile(currentPath, fileList);
            break;
        case 'x':
            FileExplorer::deleteFile(fileList.getCurrentElement().path);
            break;
        case 'f': 
            findFile(currentPath, fileList);
            return;
        case 'r':
            renameFile(fileList);
            break;      
        case 'i':
            showFileProperties(fileList);
            break;
        case HandleKeys::KEY_UP:
            fileList.previous();
            return;
        case HandleKeys::KEY_DOWN: 
            fileList.next();
            return;
        case HandleKeys::KEY_ENTER: { 
            const FileRecord& selectedFile = fileList.getCurrentElement();

            if(selectedFile.fileName == "..") {
                if(currentPath.string().length() == ROOT_SIZE_PATH) {
                    isDrives = true;
                    currentPath.clear();
                } else {
                    currentPath = currentPath.parent_path().string();
                }
            } else if(selectedFile.isDirectory) {
                currentPath = selectedFile.path.string();
            } else {
                FileExplorer::openFile(selectedFile.path);
                return;
            }
            break;
        }
        default:
            return;
        }

        reloadDirectory(currentPath, fileList, isDrives);
}


