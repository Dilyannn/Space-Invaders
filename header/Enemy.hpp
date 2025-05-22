#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameObject.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>

class Enemy : public GameObject {
public:
  explicit Enemy(int x = 0, int y = 0, char symbol = ' ', int direction = 0);
  virtual ~Enemy();
  Enemy(const Enemy& rhs);
  Enemy& operator=(const Enemy& rhs);

  int getDirection() const;
  void setDirection(int direction);

  virtual void update();
  virtual void render();

  /* std::ostream& operator<<(std::ostream& ..., const Player& ...); ... */

private:
  int direction;
};

#endif //ENEMY_HPP
