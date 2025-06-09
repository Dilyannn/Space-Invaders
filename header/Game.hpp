#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "GameObject.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Barrier.hpp"
#include "raylib.h"

#include <iostream>
#include <vector>

class Game {
public:
    Game();
    virtual ~Game();

    void input();
    void update();
    void checkCollisions();
    void render();
    void run();
    void reset();
    void gameOver();
    void initializeGame();

    bool isRunning() const {
        return runningGame;
    }
    int getLevel() const {
        return level;
    }
    int getScore() const {
        return player.getPlayerScore();
    }
    int getLives() const {
        return player.getPlayerLives();
    }

private:
    static std::vector<Barrier> createBarriers();
    std::vector<Enemy> createEnemies();
    void deleteInactiveBullets();
    void moveEnemies();
    void moveDownEnemies(int distance);

    std::vector<Barrier> barriers;
    std::vector<Enemy> enemies;
    std::vector<GameObject*> bullets;

    Player player;
    int level;
    bool runningGame;
    int enemyDirection; // +1 (->) / –1 (<-)

    std::vector<Bullet> enemyBullets;
    float timeLastEnemyShot;
    float enemyShotInterval;
    void enemyShoot();
    void deleteInactiveEnemyBullets();
};

#endif // GAME_HPP