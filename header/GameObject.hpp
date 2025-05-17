#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ColorsDraw.hpp"
#include "raylib.h"

#include <iostream>

class GameObject {
public:
    explicit GameObject(int x = 0, int y = 0);
    virtual ~GameObject();
    GameObject(const GameObject& rhs);
    GameObject& operator=(const GameObject& rhs);

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    virtual void update();
    virtual void render();

    std::ostream& inspect(std::ostream& out) const;

protected:
    Texture2D image;
    //Vector2 position;

private:
    int x, y; // coordinates
    //char symbol;
    //TODO COLORS color; // system(color 06); //0 - balck; 6 - yellow;
};

std::ostream& operator<<(std::ostream& out, const GameObject& rhs);

#endif //GAMEOBJECT_H
