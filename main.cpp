#include "raylib.h"
#include "header/Game.hpp"
#include "header/Enemy.hpp"

int main() {
    constexpr int offset = 50;
    InitWindow(750 + offset, 700 + offset * 2, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) { //WindowShouldClose() == false
        game.update();
        game.input(); // <- a; -> d
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, RED);
        DrawLineEx({20, 720}, {780, 720}, 3, RED);
        game.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}