#include "../header/Game.hpp"
#include <iostream>

Game::Game() {
    score = 0;
    level = 1;
    runningGame = true;

    barriers = createBarriers();
}

Game::~Game() {
    // ...
}

void Game::update() {
    for (auto& bullet: player.bullets) {
        bullet.update();
    }
    DeleteInactiveBullets();
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
    }else if (IsKeyDown(KEY_SPACE)) {
        player.shoot();
    }
}
void Game::DeleteInactiveBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();) {
        if (!it -> active) {
            it = player.bullets.erase(it);
        }else {
            it++;
        }
    }
}

void Game::render() {
    player.draw();
    // enemies ...

    for (auto& bullet: player.bullets) {
        bullet.Render();
    }

    for (auto& barrier : barriers ) {
        barrier.render();
    }
}

void Game::initializeEnemies() {}
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

