#include "raylib.h"
#include "header/Game.hpp"

int main() {
    InitWindow(1000, 850, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false) {
        game.input();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        game.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}