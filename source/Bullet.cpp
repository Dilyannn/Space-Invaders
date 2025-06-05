#include "../header/Bullet.hpp"
#include "raylib.h"
#include <iostream>

 Bullet::Bullet(Vector2 direction,int speed) {
     this -> direction = direction;
     this -> speed = speed;
     active = true;
 }
Bullet::Bullet(const Bullet& rhs)
    :direction(rhs.direction),
      speed(rhs.speed),
      active(rhs.active){}
 Bullet::~Bullet(){}

Bullet& Bullet::operator=(const Bullet& rhs) {
     if (this != &rhs) {
         direction = rhs.direction;
         speed     = rhs.speed;
         active    = rhs.active;

     }
     return *this;
 }

 void Bullet::Render() {
     if(active) {
         DrawRectangle(direction.x, direction.y, 4, 15, {243, 216, 63, 255});
     }
 }
 void Bullet::update() {
     direction.y += speed;
     if (active) {
         if (direction.y > GetScreenHeight() || direction.y < 0) {
             active = false;
         }
     }

}


