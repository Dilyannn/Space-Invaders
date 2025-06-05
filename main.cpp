#include "raylib.h"
#include "header/Game.hpp"
#include "header/Enemy.hpp"

int main() {
    InitWindow(1000, 850, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) { //WindowShouldClose() == false
        game.input(); // <- a; -> d

        BeginDrawing();
        ClearBackground(DARKGRAY);
        game.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}