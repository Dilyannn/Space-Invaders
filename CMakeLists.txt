cmake_minimum_required(VERSION 3.29)
project(Space-Invaders)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        Space-Invaders main.cpp
        header/Bullet.hpp
        source/Bullet.cpp
        header/ColorsDraw.hpp
        source/ColorsDraw.cpp
        header/Enemy.hpp
        source/Enemy.cpp
        header/Game.hpp
        source/Game.cpp
        header/GameObject.hpp
        source/GameObject.cpp
        header/Player.hpp
        source/Player.cpp
)