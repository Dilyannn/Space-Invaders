#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "raylib.h"

#include <iostream>

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

    Player operator+(int points) const;
    Player operator-(int points) const;

    std::ostream& ins(std::ostream& out) const;

    void reset(); // Reset position, lives, and score

private:
    int playerLives, playerScore;
    Texture2D image;
    //TODO add speed;
};

std::ostream& operator<<(std::ostream& out, const Player& rhs);

#endif // PLAYER_HPP
