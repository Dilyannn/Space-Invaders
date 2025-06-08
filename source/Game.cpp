#include "../header/Game.hpp"
#include <raylib.h>

Game::Game() {
    score = 0;
    level = 1;
    runningGame = true;

    enemyDirection = 1;
    timeLastEnemyShot = 0.0f;
    enemyShotInterval = 0.5f;

    barriers = createBarriers();
    enemies  = createEnemies();
}

Game::~Game() {}

void Game::input() {
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
    moveEnemies();
    for (auto& b : player.bullets) {
        b.update();
    }
    deleteInactiveBullets();

    enemyShoot();
    for (auto& b : enemyBullets) {
        b.update();
    }
    deleteInactiveEnemyBullets();
}


void Game::checkCollisions() {
    // TODO: bullet–enemy, bullet–barrier, enemy–barrier, etc.
}

void Game::render() {
    player.draw();

    for (auto& bullet : player.bullets) {
        bullet.render();
    }
    for (auto& barrier : barriers) {
        barrier.render();
    }
    for (auto& enemy : enemies) {
        enemy.render();
    }
    for (auto& enemyBullet : enemyBullets) {
        enemyBullet.renderEnemy();
    }
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

void Game::deleteInactiveBullets() {
    for (auto it = player.bullets.begin(); it != player.bullets.end();) {
        if (!it->active) {
            it = player.bullets.erase(it);
        } else {
            ++it;
        }
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
        moveDownEnemies(20);
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
        int indexRandomEnemy = GetRandomValue(0, (int)enemies.size() - 1);
        Enemy& e = enemies[indexRandomEnemy];
        Rectangle r = e.getRect();

        Vector2 position{
            r.x + r.width  * 0.5f,
            r.y + r.height
        };

        enemyBullets.emplace_back(position, +5);

        timeLastEnemyShot = currentTime;
    }
}

void Game::deleteInactiveEnemyBullets() {
    for (auto it = enemyBullets.begin(); it != enemyBullets.end(); ) {
        if (!it->active) {
            it = enemyBullets.erase(it);
        } else {
            ++it;
        }
    }
}
