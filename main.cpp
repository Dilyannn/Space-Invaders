#include "raylib.h"

int main() {
    // 800x450 is 16:9
    InitWindow(800, 450, "Raylib");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(SKYBLUE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

// #include "header/Game.hpp"
//
// int main() {
//     Game game;
//     game.run();
//     return 0;
// }