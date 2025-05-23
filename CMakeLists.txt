cmake_minimum_required(VERSION 3.30)
project(Space-Invaders)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

add_executable(
        Space-Invaders main.cpp
        header/Bullet.hpp
        source/Bullet.cpp
        header/Enemy.hpp
        source/Enemy.cpp
        header/Game.hpp
        source/Game.cpp
        header/GameObject.hpp
        source/GameObject.cpp
        header/Player.hpp
        source/Player.cpp
        header/Barrier.hpp
        source/Barrier.cpp
)

target_link_libraries(Space-Invaders PRIVATE raylib)