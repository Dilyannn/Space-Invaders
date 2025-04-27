#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ColorsDraw.hpp"

#include <iostream>
#include <Windows.h>

class GameObject {
public:
  explicit GameObject(int x = 0, int y = 0, char symbol = ' ');
  virtual ~GameObject();
  GameObject(const GameObject& rhs);
  GameObject& operator=(const GameObject& rhs);

  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);

  virtual void update();
  virtual void render();

  /* std::ostream& operator<<(std::ostream& ..., const Player& ...); ... */

private:
  int x, y; // coordinates
  char symbol;
  //TODO COLORS color; // system(color 06); //0 - balck; 6 - yellow;
};

 /* operator << ... ^ */

#endif //GAMEOBJECT_H
