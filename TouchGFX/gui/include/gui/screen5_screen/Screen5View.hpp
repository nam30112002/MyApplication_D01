#ifndef SCREEN5VIEW_HPP
#define SCREEN5VIEW_HPP

#include <gui_generated/screen5_screen/Screen5ViewBase.hpp>
#include <gui/screen5_screen/Screen5Presenter.hpp>

class Screen5View: public Screen5ViewBase {
public:
	Screen5View();
	virtual ~Screen5View() {
	}
	virtual void setupScreen();
	virtual void tearDownScreen();
	virtual void handleTickEvent();
protected:
	int16_t localImageX;
	touchgfx::Image bullet_list[30];
	touchgfx::Image bullet_enemy[9];
	touchgfx::ScalableImage ulti[2];
	uint32_t tickCount;
	uint32_t countItem;
	uint32_t countExploreTime;
	uint16_t isItem;
	uint16_t isDrop;
	uint16_t start;
	uint16_t isUlti;
	uint16_t ultiCount;
	uint16_t turnLeft;
	int32_t playerHP;
	int16_t bossHP;
	uint16_t isMove[30];

};

#endif // SCREEN5VIEW_HPP
