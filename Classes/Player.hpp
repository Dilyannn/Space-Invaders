#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <vector>

class Player : public GameObject {
public:
  explicit Player(int x = 0, int y = 0, char symbol = ' ', int playerLives = 3, int playerScore = 0);
  virtual ~Player();
  Player(const Player& rhs);
  Player& operator=(const Player& rhs);

  int getPlayerLives() const;
  int getPlayerScore() const;
  void setPlayerLives(int playerLives);
  void setPlayerScore(int playerScore);

  virtual void moveLeft();
  virtual void moveRight();
  virtual void shoot();

  Player operator+(int points) const;
  Player operator-(int points) const;

  /* std::ostream& operator<<(std::ostream& ..., const Player& ...); ... */

private:
  int playerLives, playerScore;
};

/* operator << ... ^ */

#endif // PLAYER_HPP
