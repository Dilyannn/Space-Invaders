#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"

#include <iostream>
#include <cstdlib>
#include <vector>

class Bullet : public GameObject {
public:
  explicit Bullet(int x = 0, int y = 0, char symbol = ' ', int direction = 0);
  virtual ~Bullet();
  Bullet(const Bullet& rhs);
  Bullet& operator=(const Bullet& rhs);

  int getDirection() const;
  void setDirection(int direction);

private:
  int direction;
};

#endif //BULLET_HPP
