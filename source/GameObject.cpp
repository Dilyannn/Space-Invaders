#include "../header/GameObject.hpp"

GameObject::GameObject(int x, int y): x(x), y(y) {
}

GameObject::~GameObject() {
}

GameObject::GameObject(const GameObject& rhs): x(rhs.x), y(rhs.y) {
}

GameObject& GameObject::operator=(const GameObject& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
    }
    return *this;
}

int GameObject::getX() const {
    return x;
}

int GameObject::getY() const {
    return y;
}

void GameObject::setX(int newX) {
    x = newX;
}

void GameObject::setY(int newY) {
    y = newY;
}

void GameObject::update() {
}

void GameObject::Render() {
    //DrawTexture(image, x, y, WHITE);
}

std::ostream& GameObject::ins(std::ostream& out) const {
    out << "GameObject at (" << x << ", " << y << ")";
    return out;
}

std::ostream& operator<<(std::ostream& out, const GameObject& rhs) {
    return rhs.ins(out);
}
