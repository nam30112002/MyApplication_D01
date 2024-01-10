#ifndef SCREEN4VIEW_HPP
#define SCREEN4VIEW_HPP
#include <vector>
#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <gui/screen4_screen/Screen4Presenter.hpp>
struct Bullet {
    uint32_t speed;
//    uint32_t isMove;
//    int16_t x;
//    int16_t y;
};
class Screen4View : public Screen4ViewBase
{
public:
    Screen4View();
    virtual ~Screen4View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();
protected:
    int16_t localImageX;
    touchgfx::Image bullet_list[30];
    touchgfx::Image enemy_list[9];
    touchgfx::Image bullet_enemy[9];
    touchgfx::Image enemyblue[9];
    touchgfx::Image enemyorange[9];
    touchgfx::Image bluelazer[9];
    touchgfx::Image orangelazer[9];
    uint32_t tickCount;
    uint32_t tickCount2;
    uint32_t tickCount3;
    uint32_t tickCount4;
    uint32_t tickCount5;
    uint32_t tickCount6;
    uint32_t tickCount7;
    uint32_t tickCount8;
    uint32_t countItem;
    uint32_t countExploreTime;
    uint16_t isItem;
    uint16_t isDrop;
    uint16_t start;
    int32_t playerHP;
    uint16_t isMove[30];

    uint16_t isActive[9];
    uint16_t isActiveBlue[9];
    uint16_t isActiveOrange[9];
    uint16_t redenemys;
};
#endif // SCREEN4VIEW_HPP
