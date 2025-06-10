#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include "GameObject.hpp"
#include "raylib.h"
#include "Bullet.hpp"
#include <vector>

class Player : public GameObject {
public:
    Player();
    explicit Player(int x, int y, int playerLives = 3, int playerScore = 0);
    virtual ~Player() override;
    Player(const Player& rhs);
    Player& operator=(const Player& rhs);

    int getPlayerLives() const;
    int getPlayerScore() const;

    void setPlayerLives(int playerLives);
    void setPlayerScore(int playerScore);

    virtual void draw();
    virtual void moveLeft();
    virtual void moveRight();
    virtual void shoot(); //TODO empty; waiting for class Bullet
    std::vector<Bullet> bullets;

    Player operator+(int points) const;
    Player operator-(int points) const;

    std::ostream& ins(std::ostream& out) const;

    void reset(); // Reset only the position

private:
    int playerLives, playerScore;
    Texture2D image;
    //TODO add speed;
    double lastFireTime;
};

std::ostream& operator<<(std::ostream& out, const Player& rhs);

#endif // PLAYER_HPP
