// Въвеждаме нужните include-и
#include "../header/Game.hpp"
#include "../header/Player.hpp"
#include <raylib.h>
#include <algorithm>

Font font1 = LoadFontEx("source/fonts/PixelGame-R9AZe.otf",64,nullptr,0);

Game::Game() {
    initializeGame();
}

Game::~Game() = default;

void Game::initializeGame() {
    barriers.clear();
    enemies.clear();
    player.bullets.clear();
    enemyBullets.clear();

    barriers = createBarriers();
    enemies  = createEnemies();

    player.setPlayerScore(0);
    player.setPlayerLives(3);

    level = 1;
    runningGame = true;

    enemyDirection = 1;
    timeLastEnemyShot = 0.0f;
    enemyShotInterval = 0.75f;
}

void Game::reset() {
    initializeGame();
}

void Game::gameOver() {
    runningGame = false;
}

void Game::input() {
    if (!runningGame) {
        if (IsKeyPressed(KEY_ENTER)) {
            reset();
        }
        return;
    }

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player.moveRight();
    }
    else if (IsKeyDown(KEY_SPACE)) {
        player.shoot();
    }
}

void Game::update() {
    if (!runningGame) {
        if (IsKeyPressed(KEY_ENTER)) {
            reset();
        }
        return;
    }

    moveEnemies();

    while (player.getPlayerScore() >= 300 && getLevel() > 1) {
        player.setPlayerLives(player.getPlayerLives() + 1);
        player.setPlayerScore(player.getPlayerScore() - 300);
    }

    for (auto& b : player.bullets) b.update();
    deleteInactiveBullets();

    enemyShoot();
    for (auto& b : enemyBullets) b.update();
    deleteInactiveEnemyBullets();

    checkCollisions();
    if (enemies.empty()) {
        if (level < 3) {
            level++;
            enemyShotInterval *= 0.5f;
            enemies = createEnemies();
        } else {
            gameOver();
        }
    }
}

bool Game::isRunning() const {
    return runningGame;
}
int Game::getLevel() const {
    return level;
}
int Game::getScore() const {
    return player.getPlayerScore();
}
int Game::getLives() const {
    return player.getPlayerLives();
}

void Game::checkCollisions() {
    for (auto& bullet : player.bullets) {
        if (!bullet.active) continue;

        for (auto& enemy : enemies) {
            if (CheckCollisionRecs(bullet.getRect(), enemy.getRect())) {
                bullet.active = false;

                enemies.erase(
                    std::remove_if(enemies.begin(), enemies.end(),
                        [&](const Enemy& e) {
                            return CheckCollisionRecs(bullet.getRect(), e.getRect());
                        }),
                    enemies.end()
                );

                player.setPlayerScore(player.getPlayerScore() + 10);
                break;
            }
        }

        for (auto& barrier : barriers) {
            auto& blocks = barrier.blocks;
            for (auto it = blocks.begin(); it != blocks.end(); ) {
                if (CheckCollisionRecs(bullet.getRect(), it->getRect())) {
                    bullet.active = false;
                    it = blocks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    for (auto& b : enemyBullets) {
        if (!b.active) continue;

        if (CheckCollisionRecs(b.getRect(), { static_cast<float>(player.getX()), static_cast<float>(player.getY()), 40, 40 })) {
            b.active = false;
            player.setPlayerLives(player.getPlayerLives() - 1);
            if (player.getPlayerLives() <= 0) {
                gameOver();
            } else {
                player.reset();
            }
        }

        for (auto& barrier : barriers) {
            auto& blocks = barrier.blocks;
            for (auto it = blocks.begin(); it != blocks.end(); ) {
                if (CheckCollisionRecs(b.getRect(), it->getRect())) {
                    b.active = false;
                    it = blocks.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}

void Game::render() {
    player.draw();

    for (auto& bullet : player.bullets) bullet.render();
    for (auto& barrier : barriers) barrier.render();
    for (auto& enemy : enemies) enemy.render();
    for (auto& enemyBullet : enemyBullets) enemyBullet.renderEnemy();

    if (!runningGame && player.getPlayerLives() <= 0) {
        DrawText("GAME OVER!", GetScreenWidth() / 2 - 90, GetScreenHeight() / 2 - 40, 30, RED);
        DrawText("Press ENTER to restart", GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 + 10, 20, WHITE);
    }
}

void Game::run() {
    while (!WindowShouldClose()) {
        input();
        update();
        BeginDrawing();
        ClearBackground(BLACK);
        render();
        EndDrawing();
    }
}

void Game::deleteInactiveBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();)
        it = !it->active ? player.bullets.erase(it) : ++it;
}

void Game::deleteInactiveEnemyBullets() {
    for (auto it = enemyBullets.begin(); it != enemyBullets.end();)
        it = !it->active ? enemyBullets.erase(it) : ++it;
}

std::vector<Barrier> Game::createBarriers() {
    std::vector<Barrier> result;
    int blockSize = 6;
    int barrierWidth = static_cast<int>(Barrier::grid[0].size()) * blockSize;
    float gapBetween = (GetScreenWidth() - (4.0f * barrierWidth)) / 5.0f;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gapBetween + i * barrierWidth;
        float offsetY = static_cast<float>(GetScreenHeight() - 200);
        result.push_back(Barrier({ offsetX, offsetY }));
    }
    return result;
}

std::vector<Enemy> Game::createEnemies() {
    std::vector<Enemy> result;
    int rows = 4, cols = 10;
    int spacingX = 50, spacingY = 50;
    int startX = 100, startY = 100;

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int type = (row % 4) + 1;
            int x = startX + col * spacingX;
            int y = startY + row * spacingY;
            result.emplace_back(type, x, y);
        }
    }
    return result;
}

void Game::moveEnemies() {
    bool hitEdge = false;

    for (auto& enemy : enemies) {
        int ex = enemy.getX();
        int ew = static_cast<int>(enemy.getRect().width);
        if (ex + ew >= GetScreenWidth() - 25) {
            enemyDirection = -1;
            hitEdge = true;
            break;
        }
        if (ex <= 25) {
            enemyDirection = 1;
            hitEdge = true;
            break;
        }
    }

    if (hitEdge) {
        moveDownEnemies(10);
    }
    for (auto& enemy : enemies) {
        enemy.setX(enemy.getX() + enemyDirection);
    }
}

void Game::moveDownEnemies(int distance) {
    for (auto& enemy : enemies) {
        enemy.setY(enemy.getY() + distance);
    }
}

void Game::enemyShoot() {
    double currentTime = GetTime();
    if (currentTime - timeLastEnemyShot >= enemyShotInterval && !enemies.empty()) {
        std::vector<Enemy> bottomEnemies;

        for (int col = 0; col < GetScreenWidth(); col += 50) {
            Enemy* bottom = nullptr;
            for (auto& e : enemies) {
                if (e.getX() >= col && e.getX() < col + 50) {
                    if (!bottom || e.getY() > bottom->getY()) {
                        bottom = &e;
                    }
                }
            }
            if (bottom) bottomEnemies.push_back(*bottom);
        }

        if (!bottomEnemies.empty()) {
            int randomIndex = GetRandomValue(0, static_cast<int>(bottomEnemies.size()) - 1);
            Enemy& shooter = bottomEnemies[randomIndex];
            Rectangle r = shooter.getRect();

            Vector2 position;
            position.x = r.x + r.width / 2;
            position.y = r.y + r.height;

            enemyBullets.emplace_back(position, 5);
            timeLastEnemyShot = currentTime;
        }
    }
}