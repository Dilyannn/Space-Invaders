#include "../header/Game.hpp"

Game::Game() {
    score = 0;
    level = 1;
    runningGame = true;

    barriers = createBarriers();
}

Game::~Game() {
    // ...
}

void Game::input() {
    if (IsKeyDown(KEY_LEFT)) {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_A)) {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_D)) {
        player.moveRight();
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.moveRight();
    }
}

void Game::render() {
    player.draw();
    // enemies ...

    for (auto& barrier : barriers ) {
        barrier.render();
    }
}

void Game::initializeEnemies() {}
void Game::update() {}
void Game::checkCollisions() {}
void Game::run() {}

std::vector<Barrier> Game::createBarriers() {
    int barrierWidth = Barrier::grid[0].size() * 3;
    float gapBetweenBarriers = (GetScreenWidth() - (4. * barrierWidth)) / 5.;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gapBetweenBarriers + i * barrierWidth; //equal gaps
        barriers.push_back(Barrier({offsetX, static_cast<float>(GetScreenHeight() - 100)}));
    }

    return barriers; //vector
}
