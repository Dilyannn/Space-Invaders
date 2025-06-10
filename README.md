# Space Invaders

A simple C++ recreation of the classic arcade game built with the [raylib](https://github.com/raysan5/raylib) graphics library.

This repository contains all game source files, images and fonts required to build the game. See [`docs/ARCHITECTURE.md`](docs/documentation.md) for a detailed description of the code structure and classes.

## Quick Start

Requirements:
- CMake 3.30+
- A C++23 compatible compiler
- raylib (fetched automatically by CMake)

To build the game:
```bash
cmake -S . -B build
cmake --build build
```
Run the resulting `Space-Invaders` executable. Use the arrow keys or **A/D** to move the ship and press **Space** to shoot.

## License

This project is released under the MIT License. See [LICENSE](LICENSE) for details.
