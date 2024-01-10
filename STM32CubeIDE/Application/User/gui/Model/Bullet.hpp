#ifndef BULLET_HPP
#define BULLET_HPP

class Bullet {
public:
    Bullet();
    void setPosition(int x, int y);
    int getX();
    int getY();


private:
    int x, y; // Vị trí của "Bullet"
    // Các thuộc tính khác của "Bullet"
};

#endif
