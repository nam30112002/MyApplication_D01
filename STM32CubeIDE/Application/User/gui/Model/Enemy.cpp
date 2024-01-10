#include "Enemy.hpp"

Enemy::Enemy() {
    // Khởi tạo các thuộc tính của "Enemy"
}

void Enemy::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Enemy::getX() {
    return x;
}

int Enemy::getY() {
    return y;
}
