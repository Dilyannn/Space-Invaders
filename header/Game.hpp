#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "GameObject.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "raylib.h"

#include <iostream>
#include <vector>

class Game {
public:
    Game();
    //TODO constructor with params;
    virtual ~Game();

    void initializeEnemies();
    void input();
    void update();
    void checkCollisions();
    void render();
    void run();

private:
    Player player;
    std::vector<GameObject*> enemies;
    std::vector<GameObject*> bullets;
    int score, level;
    bool runningGame;
};



#endif //GAME_HPP
