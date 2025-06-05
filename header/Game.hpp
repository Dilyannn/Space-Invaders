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

private:
    std::vector<Barrier> createBarriers();
    std::vector<Enemy> createEnemies();
    std::vector<Barrier> barriers;
    std::vector<Enemy> enemies;
    std::vector<GameObject*> bullets;

    Player player;
    int score, level;
    bool runningGame;
};

#endif // GAME_HPP
