#ifndef SHIP_HPP
#define SHIP_HPP

class Ship {
public:
    Ship();

    void setPosition(int x, int y);
    int getX();
    int getY();

private:
    int x, y; // Vị trí của "Ship"
    // Các thuộc tính khác của "Ship"
};

#endif
