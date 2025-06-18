#include "../header/Enemy.hpp"

Texture2D Enemy::enemyImages[4] = {};

Enemy::Enemy(int type, int x, int y): GameObject(x, y), type(type) {
    int indexType = (type - 1) % 4;
    if (indexType < 0) indexType = 0;

    if (enemyImages[indexType].id == 0) {
        const char* var = nullptr;
        switch (type) {
            case 1: var = "../source/images/invader_blue.png";  break;
            case 2: var = "../source/images/invader_green.png"; break;
            case 3: var = "../source/images/invader_red.png";   break;
            default: var = "../source/images/invader_yellow.png"; break;
        }
        enemyImages[indexType] = LoadTexture(var);
    }
    image = enemyImages[indexType];
}

Enemy::~Enemy() = default;

Enemy::Enemy(const Enemy& rhs): GameObject(rhs), type(rhs.type) {
    int indexType = (type - 1) % 4;
    if (indexType < 0) indexType = 0;
    image = enemyImages[indexType];
}

Enemy& Enemy::operator=(const Enemy& rhs) {
    if (this != &rhs) {
        GameObject::operator=(rhs);
        type = rhs.type;
        int indexType = (type - 1) % 4;
        if (indexType < 0) indexType = 0;
        image = enemyImages[indexType];
    }
    return *this;
}

void Enemy::update() {
    setX(getX() + 1);
}

void Enemy::render() {
    DrawTexture(image, getX(), getY(), WHITE);
}

int Enemy::getType() const {
    return type;
}

Rectangle Enemy::getRect() const {
    return { static_cast<float>(getX()), static_cast<float>(getY()),
        static_cast<float>(image.width), static_cast<float>(image.height)
    };
}

void Enemy::unloadImages() {
    for (auto & enemyImage : enemyImages) {
        if (enemyImage.id != 0) {
            UnloadTexture(enemyImage);
            enemyImage.id = 0;
        }
    }
}
