#include "../header/Game.hpp"

Game::Game() {
    score = 0;
    level = 1;
    runningGame = true;
}

Game::~Game() {
    // ...
}

void Game::input() {
    if (IsKeyDown(KEY_LEFT)) {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_RIGHT)) {
        player.moveRight();
    }
}

void Game::render() {
    player.draw();
    // enemies ...
}

void Game::initializeEnemies() {}
void Game::update() {}
void Game::checkCollisions() {}
void Game::run() {}

std::vector<Barrier> Game::createBarriers() {

}
