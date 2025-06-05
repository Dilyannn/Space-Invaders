#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameObject.hpp"
#include "raylib.h"

class Enemy : public GameObject {
public:
  Enemy(int type, int x, int y);
  virtual ~Enemy();
  Enemy(const Enemy& rhs);
  Enemy& operator=(const Enemy& rhs);

  void update() override;
  void render() override;

  int getType() const;
  Rectangle getRect() const;

private:
  int type;
  Texture2D image;
};

#endif // ENEMY_HPP
