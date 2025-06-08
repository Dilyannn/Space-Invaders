#include "../header/Bullet.hpp"
#include "raylib.h"

Bullet::Bullet(Vector2 direction,int speed) {
     this->direction = direction;
     this->speed = speed;
     active = true;
 }
Bullet::Bullet(const Bullet& rhs): direction(rhs.direction), speed(rhs.speed), active(rhs.active) {}

Bullet::~Bullet() {}

Bullet& Bullet::operator=(const Bullet& rhs) {
     if (this != &rhs) {
         direction = rhs.direction;
         speed = rhs.speed;
         active = rhs.active;
     }
     return *this;
}

void Bullet::render() {
    if(active) {
        DrawRectangle(direction.x, direction.y, 4, 15, RED);
    }
}
void Bullet::renderEnemy() {
    if (!active) return;
    static constexpr Color colors[] = { GOLD, ORANGE, YELLOW };
    int indexRandomColor = GetRandomValue(0, 3);

    DrawRectangle(
        static_cast<int>(direction.x),
        static_cast<int>(direction.y),
        4, 15,
        colors[indexRandomColor]
    );
}

void Bullet::update() {
    direction.y += speed;
    if (active) {
        if (direction.y > GetScreenHeight() || direction.y < 0) active = false;
    }
}