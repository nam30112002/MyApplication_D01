#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy {
public:
    Enemy();

    void setPosition(int x, int y);
    int getX();
    int getY();

private:
    int x, y; // Vị trí của "Enemy"
    // Các thuộc tính khác của "Enemy"
};

#endif
