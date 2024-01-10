#include "Bullet.hpp"

Bullet::Bullet() {
    // Khởi tạo các thuộc tính của "Bullet"
}

void Bullet::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Bullet::getX() {
    return x;
}

int Bullet::getY() {
    return y;
}
