#ifndef BARRIER_HPP
#define BARRIER_HPP

#include <iostream>
#include <vector>

#include "raylib.h"

class Block {
public:
    explicit Block(Vector2 position);
    void render();
    Rectangle getRect();
private:
    Vector2 position;
};

class Barrier {
public:
    Barrier(Vector2 position);
    void render();
    Vector2 position;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
private:
};

#endif //BARRIER_HPP
