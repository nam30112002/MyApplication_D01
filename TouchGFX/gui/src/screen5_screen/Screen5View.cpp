#include <gui/screen5_screen/Screen5View.hpp>
#include "cmsis_os.h"
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/Image.hpp>

extern osMessageQueueId_t Queue1Handle;

Screen5View::Screen5View() {
	countExploreTime = 0;
	isItem = 0;
	isDrop = 0;
	isUlti = 0;
	ultiCount = 0 ;
	turnLeft = 1 ;
	countItem = 0;
	playerHP = 85;
	bossHP = 100;
	hpplayer.setPosition(10, 11, 85, 9);
	 ultimate.setPosition(234, 150, 54, 2);
	for(int16_t i  = 0 ;i <2;i++){
		ulti[i].setBitmap(touchgfx::Bitmap(BITMAP_UNTIMATE_ID));
		ulti[i].setPosition(70, 104, 54, 0);
		ulti[i].setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
		add(ulti[i]);
	}



	tickCount = 0;
	for (int16_t i = 0; i < 30; i++) {
			bullet_list[i].setXY(110, -23);
			bullet_list[i].setBitmap(touchgfx::Bitmap(BITMAP_BULLET_ID));
			add(bullet_list[i]);
			isMove[i] = 0;

		}
}
void controlB(touchgfx::Image &player, touchgfx::BoxWithBorderButtonStyle< touchgfx::RepeatButtonTrigger >  rightButton, touchgfx::BoxWithBorderButtonStyle< touchgfx::RepeatButtonTrigger >  leftButton){
	int16_t x = player.getX();
	if(rightButton.getPressed()==1){
			x+=3;
			if(x>240){
				x=0;
			}
			player.setX(x);
		}
		if(leftButton.getPressed()==1){
			x-=3;
			if(x<0){
				x=240;
			}
			player.setX(x);
		}
}
void bossMove(touchgfx::Image &boss,int16_t speed,int16_t direct){
	int16_t x = boss.getX();
	if(direct == 0){
		boss.setX(x-speed);
	}
	if(direct ==1){
		boss.setX(x+speed);
	}
}
void bossUlti(touchgfx::Image &boss,touchgfx::ScalableImage &ulti,int16_t ulti_speed,int16_t x_axis,int16_t y_axis){
	int16_t x = boss.getX();
	int16_t y = boss.getY();
	ulti.setPosition(x+x_axis,y+y_axis,54,30+ulti_speed);
}


void bossAttach(touchgfx::Image &boss, touchgfx::Image &bullet,
		int16_t isMove, int16_t bullet_speed,int16_t x_axis,int16_t y_axis) {
	int16_t x = boss.getX();
	int16_t y = boss.getY();
	if (isMove == 1) {
		bullet.setY(bullet.getY() + bullet_speed);
	}
	if (isMove == 0) {
		bullet.setXY(x + x_axis, y + y_axis);
	}
}

bool checkCollisionB(const touchgfx::Image &image1,
		const touchgfx::Image &image2) {

	touchgfx::Rect image1Rect = image1.getRect();
	int16_t x1 = image1Rect.x;
	int16_t y1 = image1Rect.y;
	int16_t width1 = image1Rect.width;
	int16_t height1 = image1Rect.height;

	touchgfx::Rect image2Rect = image2.getRect();
	int16_t x2 = image2Rect.x;
	int16_t y2 = image2Rect.y;
	int16_t width2 = image2Rect.width;
	int16_t height2 = image2Rect.height;

	if (x1 < (x2 + width2) && (x1 + width1) > x2 && y1 < (y2 + height2)
			&& (y1 + height1) > y2) {
		return true;
	}
	return false;
}

void Screen5View::setupScreen() {
	Screen5ViewBase::setupScreen();
}

void Screen5View::tearDownScreen() {
	Screen5ViewBase::tearDownScreen();
}
void Screen5View::handleTickEvent() {
	//set HP bar increase or decrease
	int16_t xb = boss.getX();
	int16_t yb = boss.getY();
	if (playerHP <= 0) {
		application().gotoScreen3ScreenSlideTransitionEast();
	}
	if(bossHP<=0){
		application().gotoScreen6ScreenSlideTransitionEast();
	}
	if(bossHP==70 or bossHP==30){
		isUlti=1;
	}
	if(ultiCount==50){
		isUlti=0;
		ultiCount=0;
		for(int16_t i=0;i<2;i++){
			ulti[i].setVisible(false);
			ulti[i].setHeight(0);
		}
	}
	if(isUlti==1){
		ultiCount+=1;
		for(int16_t i=0;i<2;i++){
					ulti[i].setVisible(true);
				}
		ulti[0].setPosition(xb+24,yb+70,54,ulti[0].getHeight()+10);
		ulti[1].setPosition(xb+70,yb+70,54,ulti[1].getHeight()+10);
	}
	for(int16_t i= 0 ;i< 2;i++){
		if(checkCollisionB(ulti[i],playerShip)){
			playerHP -= 1;
			hpplayer.setPosition(10, 11, playerHP, 9);
			explore.setXY(playerShip.getX(), playerShip.getY());
			explore.setVisible(true);
			countExploreTime = 4;
		}
	}
	Screen5ViewBase::handleTickEvent();
	int16_t x = playerShip.getX();
	int16_t y = playerShip.getY();
	tickCount++;
	// Boss Move
	if(turnLeft == 1){
		bossMove(boss,6,0);
	}
	else bossMove(boss,6,1);
	if(boss.getX()<=-74){
		turnLeft = 0;
	}
	if(boss.getX()>=166){
		turnLeft =1;
	}
// player attach
	for(int i= 0;i<30;i++){
		if(checkCollisionB(bullet_list[i],boss) ){
			explore.setXY(bullet_list[i].getX(), bullet_list[i].getY()-20);
			bossHP -= 3;
			hpboss.setPosition(70,241,bossHP,3);
			explore.setVisible(true);
			bullet_list[i].setY(-23);
			countExploreTime = 4;

		}
		if(checkCollisionB(bullet_list[i],bossLazer)){
			explore.setXY(bullet_list[i].getX(), bullet_list[i].getY());
			explore.setVisible(true);
			bullet_list[i].setY(-23);
			countExploreTime = 4;

		}
	}
	// Check Item X3 Bullet
	if (tickCount % 100 == 0) {
		isDrop = 1;
	}
	if (isDrop == 1) {
		x3.setY(x3.getY() + 5);
	}
	if (x3.getY() > 320) {
		isDrop = 0;
		x3.setY(-20);
	}

	if(checkCollisionB(playerShip,bossLazer)){
		playerHP -= 10;
		bossLazer.setY(320);
		hpplayer.setPosition(10, 11, playerHP, 9);
		explore.setXY(playerShip.getX(), playerShip.getY());
		explore.setVisible(true);
		countExploreTime = 4;
	}

	if (checkCollisionB(x3, playerShip)) {
		isItem = 1;
		x3.setY(-20);
		isDrop = 0;
	}
	if (isItem == 1) {
		countItem += 1;
		if (isMove[10 + tickCount / 10 % 10] == 0) {
			isMove[10 + tickCount / 10 % 10] = 1;
			isMove[20 + tickCount / 10 % 10] = 1;
			bullet_list[10 + tickCount / 10 % 10].setXY(x - 3, y - 15);
			bullet_list[20 + tickCount / 10 % 10].setXY(x + 18, y - 15);
		}
		for (int16_t i = 10; i < 30; i++) {
			bullet_list[i].setY(bullet_list[i].getY() - 5);
			if (bullet_list[i].getY() <= -23) {
				isMove[i] = 0;
			}
		}
		if (countItem >= 100) {
			isItem = 0;
			countItem = 0;
			for (int16_t i = 10; i < 30; i++) {
				bullet_list[i].setY(-50);
			}

		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	//boss attach
	if(bossLazer.getY()>=320){
		bossAttach(boss, bossLazer ,0,8,55,80);
	}
	else bossAttach(boss, bossLazer ,1,8,55,80);
	//Move the bullet of player
	if (isMove[tickCount / 10 % 10] == 0) {
		isMove[tickCount / 10 % 10] = 1;
		bullet_list[tickCount / 10 % 10].setXY(x + 8, y - 15);
	}
	for (int16_t i = 0; i < 10; i++) {
		bullet_list[i].setY(bullet_list[i].getY() - 5);
		if (bullet_list[i].getY() <= -23) {
			isMove[i] = 0;
		}
	}

//
	if (countExploreTime > 0)
		countExploreTime -= 1;
	if (countExploreTime == 0)
		explore.setVisible(false);

	//Kill enemy when hit the bullet
	controlB(playerShip,rightButton,leftButton);
	uint8_t res = 0;
	uint32_t count = osMessageQueueGetCount(Queue1Handle);
	if (count > 0) {
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if (res == 'R') {
			x += 3;
			if (x > 240) {
				x = 0;
			}
			playerShip.setX(x);
		}
		if (res == 'L') {
			x -= 1;
			if (x < 0) {
				x = 240;
			}
			playerShip.setX(x);
		}
	}

	invalidate();
}
