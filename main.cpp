#include "raylib.h"
#include "header/Game.hpp"

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

int main() {
    constexpr float OFFSET = 50.0f;
    InitWindow(750 + OFFSET, 700 + OFFSET * 2, "Space Invaders");

    Font font = LoadFontEx("source/fonts/PixelGame-R9AZe.otf",64,nullptr,0);
    Texture2D playerSpaceshipImage = LoadTexture("../source/images/spaceship.png");

    if (font.texture.id == 0) TraceLog(LOG_WARNING, "Font failed to load!");
    if (playerSpaceshipImage.id == 0) TraceLog(LOG_WARNING, "Player spaceship image failed to load!");

    SetTargetFPS(60);
    Game game;

    while (!WindowShouldClose()) {
        game.input();
        game.update();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRoundedLinesEx({10,10,780,780},0.18f,20,2,RED);
        DrawLineEx({20,720},{780,720},3,RED);

        float x = 55.0f;
        float y = ((700.0f + OFFSET * 2.0f) - (1.5 * static_cast<float>(playerSpaceshipImage.height))) + 5.0f; // FINAL VERSION DON`T TOUCH
        int lives = game.getLives();

        for (int i = 0; i < lives; i++) {
            DrawTextureV(playerSpaceshipImage, { x, y }, WHITE);
            x += 50.0f;
        }

        switch (game.getLevel()) {
            case 1:
                DrawTextEx(font, "LEVEL 01", {600,740}, 34,2,RED); break;
            case 2:
                DrawTextEx(font, "LEVEL 02", {600,740}, 34,2,RED); break;
            case 3:
                DrawTextEx(font, "LEVEL 03", {600,740}, 34,2,RED); break;
            default: ;
        }

        if (!game.isRunning()) {
            if (game.getLives() > 0) {
                DrawText("YOU WON!!!",GetScreenWidth()/2 - 90,GetScreenHeight()/2 - 40,30, RED);
                DrawText("Press ENTER to restart",GetScreenWidth()/2 - 120,GetScreenHeight()/2 + 10,20, WHITE);
                if (IsKeyPressed(KEY_ENTER)) {
                    game.reset();
                }
            } else {
                DrawTextEx(font, "", {560,740}, 34,2,RED);
            }
        }

        DrawTextEx(font, "SCORE", {50, 20}, 34, 2, RED);
        std::string scoreText = FormatWithLeadingZeros(game.getScore(), 5);
        DrawTextEx(font, scoreText.c_str(), {50, 50}, 34, 2, RED);

        game.render();
        EndDrawing();
    }

    UnloadFont(font);
    UnloadTexture(playerSpaceshipImage);
    CloseWindow();

    return 0;
}
