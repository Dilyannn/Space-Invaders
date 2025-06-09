#include "raylib.h"
#include "header/Game.hpp"

int main() {
    constexpr float OFFSET = 50.0f;
    InitWindow(750 + OFFSET, 700 + OFFSET * 2, "Space Invaders");

    Font font = LoadFontEx("source/fonts/PixelGame-R9AZe.otf",64,nullptr,0);
    Texture2D shipIcon = LoadTexture("../source/images/spaceship.png");

    if (font.texture.id == 0) TraceLog(LOG_WARNING, "Font failed to load!");
    if (shipIcon.id == 0) TraceLog(LOG_WARNING, "Ship icon failed to load!");

    SetTargetFPS(60);
    Game game;

    while (!WindowShouldClose()) {
        game.input();
        game.update();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,RED);
        DrawLineEx({20,720},{780,720},3,RED);

        if (game.isRunning()) {
            DrawTextEx(font, "LEVEL 01", {600,740}, 34,2,RED);
        } else {
            DrawTextEx(font, "GAME OVER", {560,740}, 34,2,RED);
        }

        float x = 55.0f;
        float y = ((700.0f + OFFSET * 2.0f) - (1.5 * static_cast<float>(shipIcon.height))) + 5.0f; // FINAL VERSION DON`T TOUCH
        int lives = game.getLives();

        for (int i = 0; i < lives; i++) {
            DrawTextureV(shipIcon, { x, y }, WHITE);
            x += 50.0f;
        }

        game.render();
        EndDrawing();
    }

    UnloadFont(font);
    UnloadTexture(shipIcon);
    CloseWindow();

    return 0;
}
