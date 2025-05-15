#include "raylib.h"

int main() {
    InitWindow(1000, 850, "Raylib");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}