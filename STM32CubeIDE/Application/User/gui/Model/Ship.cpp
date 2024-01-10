#include "Ship.hpp"

Ship::Ship() {
    // Khởi tạo các thuộc tính của "Ship"
}

void Ship::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int Ship::getX() {
    return x;
}

int Ship::getY() {
    return y;
}
