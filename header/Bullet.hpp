#ifndef BULLET_HPP
#define BULLET_HPP

#include "GameObject.hpp"
#include "raylib.h"

#include <iostream>
#include <cstdlib>
#include <vector>

class Bullet : public GameObject {
public:
  explicit Bullet(Vector2 direction ,int speed);
  virtual ~Bullet();
  Bullet(const Bullet& rhs);
  Bullet& operator=(const Bullet& rhs);

  int getDirection() const;
  void setDirection(int direction);
  void update();
  void render();
  void draw();
  Rectangle getRect();
  bool active;


private:
  Vector2 direction;
  int speed;

};

#endif //BULLET_HPP
