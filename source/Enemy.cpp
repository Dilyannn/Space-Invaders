#include "../header/Enemy.hpp"

Enemy::Enemy(int type, int x, int y): GameObject(x, y), type(type) {
    switch (type) {
        case 1: image = LoadTexture("../source/images/invader_blue.png");
        break;
        case 2: image = LoadTexture("../source/images/invader_green.png");
        break;
        case 3: image = LoadTexture("../source/images/invader_red.png");
        break;
        default: image = LoadTexture("../source/images/invader_yellow.png");
    }
}

Enemy::~Enemy() {
    UnloadTexture(image);
}

Enemy::Enemy(const Enemy& rhs): GameObject(rhs), type(rhs.type) {
    image = LoadTextureFromImage(LoadImageFromTexture(rhs.image));
}

Enemy& Enemy::operator=(const Enemy& rhs) {
    if (this != &rhs) {
        GameObject::operator=(rhs);
        type = rhs.type;
        UnloadTexture(image);
        image = LoadTextureFromImage(LoadImageFromTexture(rhs.image));
    }
    return *this;
}

void Enemy::update() {
    setX(getX() + 1); // move right ->, d
}

void Enemy::render() {
    DrawTexture(image, getX(), getY(), WHITE);
}

int Enemy::getType() const {
    return type;
}

Rectangle Enemy::getRect() const {
    return { (float)getX(), (float)getY(), (float)image.width, (float)image.height };
}
