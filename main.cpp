#include "raylib.h"
#include "header/Game.hpp"

int main() {
    InitWindow(1000, 850, "Space Invaders");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) { //WindowShouldClose() == false
        game.input(); // <-; ->
        game.update();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        game.render();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}