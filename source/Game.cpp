#include "../header/Game.hpp"

Game::Game() {
    score = 0;
    level = 1;
    runningGame = true;

    barriers = createBarriers();
    enemies = createEnemies();
}

Game::~Game() {
}

void Game::input() {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player.moveRight();
    }
}

void Game::render() {
    player.draw();

    for (auto& enemy : enemies) {
        enemy.render();
    }

    for (auto& barrier : barriers) {
        barrier.render();
    }
}

void Game::update() {
    for (auto& enemy : enemies) {
        enemy.update();
    }
}

void Game::checkCollisions() {
    // TODO collisions
}

void Game::run() {
    while (runningGame && !WindowShouldClose()) {
        input();
        update();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        render();
        EndDrawing();
    }
}

std::vector<Barrier> Game::createBarriers() {
    std::vector<Barrier> result;
    int blockSize = 6;
    int barrierWidth = static_cast<int>(Barrier::grid[0].size()) * blockSize;
    float gapBetween = (GetScreenWidth() - (4.0f * barrierWidth)) / 5.0f;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gapBetween + i * barrierWidth;
        float offsetY = static_cast<float>(GetScreenHeight() - 100);
        result.push_back(Barrier({ offsetX, offsetY }));
    }
    return result;
}

std::vector<Enemy> Game::createEnemies() {
    std::vector<Enemy> result;
    int rows = 4, cols = 12;
    int spacingX = 50, spacingY = 50;
    int startX = 100, startY = 100;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int type = row + 1;
            int x = startX + col * spacingX;
            int y = startY + row * spacingY;
            result.emplace_back(type, x, y);
        }
    }
    return result;
}
