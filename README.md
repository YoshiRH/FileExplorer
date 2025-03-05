# FileExplorer

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.27-%23008FBA)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)

**FileExplorer** is a lightweight, command-line-based file explorer written in C++. It allows users to navigate through directories, view files, create and delete files/directories, search for files, and more. The program is designed to be simple, fast, and easy to use, making it a handy tool for basic file management tasks.

---

## Features

- **Directory Navigation**: Browse through directories and drives seamlessly.
- **File Operations**:
  - Create new files and directories.
  - Delete files and directories.
  - Rename files and directories.
  - View file contents.
- **Search Functionality**: Search for files by name within the current directory and subdirectories.
- **File Properties**: View detailed information about files and directories, including size, type, and last modified date.
- **Cross-Platform**: Works on both Windows and Linux systems.
- **User-Friendly Interface**: Simple and intuitive command-line interface with keyboard controls.

---

## How to Use

### Prerequisites
- **CMake 3.27** or newer ([Download CMake](https://cmake.org/download/))
- C++17 compatible compiler (e.g., `g++`, `clang`, or `MSVC`)

### Installation

1. **Clone the Repository:**:
   ```bash
   git clone https://github.com/YoshiRH/FileExplorer.git
   cd FileExplorer

2. **Build with CMake:**:
   - Ensure you have a C++ compiler installed (e.g., g++ or MSVC).
   - Compile the program using the following command:
   ```bash
   mkdir build && cd build       # Create a build directory
   cmake ..                     # Configure the project
   cmake --build .              # Compile the program
   ```

3. **Run the Program:**:
   - On Windows
   ```bash
   ./FileExplorer.exe
   ```
   - On Linux
   ```bash
   ./FileExplorer
   ```

### Controls
Key	    Action  
↑ / ↓ - Navigate up and down the file list  
Enter - Open a directory or file  
D - Create a new directory  
Z - Create a new .txt file  
X - Delete a file or directory  
F - Search for a file by name  
R - Rename a file or directory  
I - View file/directory properties  
Q - Quit the program  

## Screenshots
![image](https://github.com/user-attachments/assets/3b268b41-5301-4397-9d1a-c8c7bb56ccf3)  
![image](https://github.com/user-attachments/assets/c7ca1984-cecb-4e0a-9721-8cb5b3d1d398)



## License
This project is licensed under the MIT License
