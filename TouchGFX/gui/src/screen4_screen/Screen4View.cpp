#include <gui/screen4_screen/Screen4View.hpp>
#include "cmsis_os.h"
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <ctime>

extern osMessageQueueId_t Queue1Handle;

Screen4View::Screen4View() {
	tickCount2 = 0;
	tickCount3 = 0;
	tickCount4 = 0;
	tickCount5 = 0;
	tickCount6 = 0;
	tickCount7 = 0;
	tickCount8 = 0;
	countExploreTime = 0;
	isItem = 0;
	isDrop = 0;
	start = 0;
	countItem = 0;
	playerHP = 85;
	hpplayer.setPosition(10, 11, 85, 9);
	redenemys = 0;
	tickCount = 0;
	//create 10 bullet
	for (int16_t i = 0; i < 30; i++) {
		bullet_list[i].setXY(110, -100);
		bullet_list[i].setBitmap(touchgfx::Bitmap(BITMAP_BULLET_ID));
//		bullet_x31[i].setXY(110, -23);
//		bullet_x31[i].setBitmap(touchgfx::Bitmap(BITMAP_BULLET_ID));
//		bullet_x32[i].setXY(110, -23);
//		bullet_x32[i].setBitmap(touchgfx::Bitmap(BITMAP_BULLET_ID));
		add(bullet_list[i]);
//		add(bullet_x31[i]);
//		add(bullet_x32[i]);
		isMove[i] = 0;

	}
	//create 9 enemy
	for (int16_t i = 0; i < 9; i++) {
		isActive[i] = 1;
		bullet_enemy[i].setXY(89, 320);
		bullet_enemy[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMYBULLET_ID));
		add (bullet_enemy[i]);
		if (i < 5) {
			enemy_list[i].setXY(55 * i, 25);
		} else if (i < 9) {
			enemy_list[i].setXY(27 + 55 * (i - 5), 60);
		}
		enemy_list[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMY_ID));
		add (enemy_list[i]);
	}
	for (int16_t i = 0; i < 9; i++) {
		isActiveBlue[i] = 1;
		isActiveOrange[i] = 1;
		enemyblue[i].setXY(320, -28);
		enemyblue[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMYBLE_ID));

		enemyorange[i].setXY(400, 300);
		enemyorange[i].setBitmap(touchgfx::Bitmap(BITMAP_ENEMYORANGE_ID));

		bluelazer[i].setXY(196, 320);
		bluelazer[i].setBitmap(touchgfx::Bitmap(BITMAP_BLUELAZER_ID));

		orangelazer[i].setXY(121, 320);
		orangelazer[i].setBitmap(touchgfx::Bitmap(BITMAP_ORANGELZER_ID));

		add (enemyblue[i]);
		add (enemyorange[i]);
		add (bluelazer[i]);
		add (orangelazer[i]);

	}

}
void control(touchgfx::Image &player, touchgfx::BoxWithBorderButtonStyle< touchgfx::RepeatButtonTrigger >  rightButton, touchgfx::BoxWithBorderButtonStyle< touchgfx::RepeatButtonTrigger >  leftButton){
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
bool checkCollision(const touchgfx::Image &image1,
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
// Hàm để enemy di chuyển ngẫu nhiên

void moveEnemyRandomly(touchgfx::Image &enemy, int16_t stepSize,
		int16_t tickCount) {

	if (tickCount < 50) {
		enemy.setX(enemy.getX() - stepSize);
	} else if (tickCount < 70) {
		enemy.setY(enemy.getY() + stepSize);
	} else if (tickCount < 80) {
		enemy.setX(enemy.getX() + stepSize);
		enemy.setY(enemy.getY() - stepSize);
	} else {
		enemy.setX(enemy.getX() + stepSize);
	}

	if (enemy.getX() >= 260) {
		enemy.setX(0);
	}
}
void explosion(touchgfx::Image &enemy, touchgfx::AnimatedImage explore) {
	explore.setXY(enemy.getX(), enemy.getY());
	explore.setVisible(true);
}
void remove(touchgfx::Image &enemy, touchgfx::Image &bullet) {
	enemy.setXY(400, 300);
	bullet.setXY(400, 300);
	bullet.setVisible(false);
	enemy.setVisible(false);
}
void moveStraight(touchgfx::Image &enemy, int16_t stepSize, int16_t tickCount,
		int16_t x_A, int16_t y_A, int16_t x_B, int16_t y_B) {
	int16_t vector_a = x_A - x_B;
	int16_t vector_b = y_A - y_B;
	enemy.setX(x_A - tickCount * vector_a / 50);
	enemy.setY(y_A - tickCount * vector_b / 50);
}

void enemyAttack(touchgfx::Image &enemy, touchgfx::Image &bullet,
		int16_t isMove, int16_t bullet_speed, int16_t x_axis) {
	int16_t x = enemy.getX();
	int16_t y = enemy.getY();
	if (isMove == 1) {
		bullet.setY(bullet.getY() + bullet_speed);
	}
	if (isMove == 0) {
		bullet.setXY(x + 3, y + 18);
	}
}

void Screen4View::setupScreen() {
	Screen4ViewBase::setupScreen();

}

void Screen4View::tearDownScreen() {
	Screen4ViewBase::tearDownScreen();
}

void Screen4View::handleTickEvent() {
	//set HP bar increase or decrease

	if (playerHP <= 0) {
		application().gotoScreen3ScreenSlideTransitionEast();
	}

	Screen4ViewBase::handleTickEvent();
	int16_t x = playerShip.getX();
	int16_t y = playerShip.getY();
	tickCount++;

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

	if (checkCollision(x3, playerShip)) {
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

	//enemy move
	if (redenemys < 9) {
		for (int16_t i = 0; i < 9; i++) {
			moveEnemyRandomly(enemy_list[i], 2, tickCount);
		}
	}

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
	//Enemy attack
	for (int16_t i = 0; i < 9; i++) {
		if (isActive[i]) {
			if (bullet_enemy[i].getY() >= 320) {
				enemyAttack(enemy_list[i], bullet_enemy[i], 0, 5, 3);

			} else {
				enemyAttack(enemy_list[i], bullet_enemy[i], 1, 5, 3);

			}
			if (checkCollision(bullet_enemy[i], playerShip)) {
				playerHP = playerHP - 5;
				hpplayer.setPosition(10, 11, playerHP, 9);
				bullet_enemy[i].setY(320);

			}
		}
	}
	for (int16_t i = 0; i < 9; i++) {
		if (isActiveBlue[i]) {
			if (bluelazer[i].getY() >= 320) {
				enemyAttack(enemyblue[i], bluelazer[i], 0, 5, 3);

			} else {
				enemyAttack(enemyblue[i], bluelazer[i], 1, 5, 3);

			}
			if (checkCollision(bluelazer[i], playerShip)) {
				playerHP = playerHP - 7;
				hpplayer.setPosition(10, 11, playerHP, 9);
				bluelazer[i].setY(320);
			}
		}
	}
	for (int16_t i = 0; i < 9; i++) {
		if (isActiveOrange[i]) {
			if (orangelazer[i].getY() >= 320) {
				enemyAttack(enemyorange[i], orangelazer[i], 0, 5, 3);

			} else {
				enemyAttack(enemyorange[i], orangelazer[i], 1, 5, 3);

			}
			if (checkCollision(orangelazer[i], playerShip)) {
				playerHP = playerHP - 8;
				hpplayer.setPosition(10, 11, playerHP, 9);
				orangelazer[i].setY(320);
			}
		}
	}

	if (countExploreTime > 0)
		countExploreTime -= 1;
	if (countExploreTime == 0) {
		explore.setVisible(false);
	}
	//Kill enemy when hit the bullet
	for (int16_t i = 0; i < 30; i++) {
		for (int16_t j = 0; j < 9; j++) {
			if (checkCollision(bullet_list[i], enemy_list[j])) {
				if (isActive[j] == 1) {
					isActive[j] = 0;
					enemy_list[j].setVisible(false);
					bullet_enemy[j].setVisible(false);
					explore.setXY(enemy_list[j].getX(), enemy_list[j].getY());
					explore.setVisible(true);
					countExploreTime = 4;
					redenemys += 1;
				}

			}
			if (checkCollision(bullet_list[i], enemyblue[j])) {
				if (isActiveBlue[j] == 1) {
					isActiveBlue[j] = 0;
					enemyblue[j].setVisible(false);
					bluelazer[j].setVisible(false);
					explore.setXY(enemyblue[j].getX(), enemyblue[j].getY());
					explore.setVisible(true);
					countExploreTime = 4;
					redenemys += 1;
				}
			}
			if (checkCollision(bullet_list[i], enemyorange[j])) {
				if (isActiveOrange[j] == 1) {
					isActiveOrange[j] = 0;
					enemyorange[j].setVisible(false);
					orangelazer[j].setVisible(false);
					explore.setXY(enemyorange[j].getX(), enemyorange[j].getY());
					explore.setVisible(true);
					countExploreTime = 4;
					redenemys += 1;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//Round 2

	if (redenemys == 9) {
		for (int16_t i = 0; i < 9; i++) {
			enemy_list[i].setVisible(true);
			bullet_enemy[i].setVisible(true);
			isActive[i] = 1;
		}
	}
	if (redenemys >= 9 and redenemys <= 18) {
		tickCount2 += 1;
		if (enemy_list[8].getX() > 136)
			tickCount2 = 0;
		for (int16_t i = 0; i < 9; i++) {

			if (i < 5) {
				moveStraight(enemy_list[i], 1, tickCount2, 241 + i * 20,
						86 + i * 20, 128 - (4 - i) * 20, -20 - (4 - i) * 20);
			} else {
				moveStraight(enemy_list[i], 1, tickCount2, -21 - (-5 + i) * 20,
						86 + (i - 5) * 20, 95 + (4 + 5 - i) * 20,
						-20 - (4 + 5 - i) * 20);
			}

		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//Round 3

	if (redenemys == 18) {
		for (int16_t i = 0; i < 9; i++) {
			enemyblue[i].setVisible(true);
			bluelazer[i].setVisible(true);
			isActiveBlue[i] = 1;
		}
	}
	if (redenemys >= 18 and redenemys <= 27) {
		tickCount3 += 1;
		if (enemyblue[8].getX() > 250)
			tickCount3 = 0;
		for (int16_t i = 0; i < 9; i++) {
			if (i < 5) {
				moveStraight(enemyblue[i], 1, tickCount3, 241 + i * 30, 86,
						-20 - (4 - i) * 30, 86);
			} else {
				moveStraight(enemyblue[i], 1, tickCount3, -20 - (-5 + i) * 30,
						59, 241 + (9 - i) * 30, 59);
			}

		}
	}

	//Round 4
	if (redenemys == 27) {
		for (int16_t i = 0; i < 5; i++) {
			enemyorange[i].setVisible(true);
			orangelazer[i].setVisible(true);
			isActiveOrange[i] = 1;
		}
	}
	if (redenemys >= 27 and redenemys <= 32) {
		if (tickCount4 >= 100)
			tickCount4 = 0;
		tickCount4 += 1;
		for (int16_t i = 0; i < 5; i++) {
			if (tickCount4 <= 50)
				moveStraight(enemyorange[i], 1, tickCount4, 240 + i * 40, 120,
						240 + i * 40 - 360, 120);
			else if (tickCount4 <= 100) {
				moveStraight(enemyorange[i], 1, tickCount4 - 50, -120 + i * 40,
						40, -120 + i * 40 + 360, 40);
			}
		}
	}

//				//Round 6
//					if(redenemys == 9){
//						for(int16_t i = 0 ; i < 1 ;i++){
//						enemyorange[i].setVisible(true);
//						orangelazer[i].setVisible(true);
//						isActive[i]=1;
//						}
//					}
//					if(redenemys >= 9){
//						if (tickCount6 >= 100)  tickCount6 =0;
//				        tickCount6+=1;
//						for(int16_t i = 0 ; i < 1 ;i++){
//				            if (tickCount6 <= 50) moveStraight(enemyorange[i],1,tickCount6,240,60,160,60);
//				            else if (tickCount6 <= 75) {
//				                moveStraight(enemyorange[i],1,2*(tickCount6-50),160,60,110,10);
//						    }
//				            else if (tickCount6 <= 100) {
//				                moveStraight(enemyorange[i],1,2*(tickCount6-75),110,10,60,60);
//						    }
//				            else if (tickCount6 <= 125) {
//				                moveStraight(enemyorange[i],1,2*(tickCount6-100),60,60,110,110);
//						    }
//				            else if (tickCount6 <= 150) {
//				                moveStraight(enemyorange[i],1,2*(tickCount6-125),110,110,160,60);
//						    }
//				            else moveStraight(enemyorange[i],1,tickCount6,160,60,240,60);
//				        }
//					}
//			if(redenemys == 32){
//						for(int16_t i = 0 ; i < 9 ;i++){
//							enemyblue[i].setVisible(true);
//							bluelazer[i].setVisible(true);
//							isActiveBlue[i]=1;
//						}
//					}
//					if(redenemys >= 32 ){
//						tickCount5+=1;
//						for(int16_t i = 0 ; i < 5 ;i++){
//							if(start == 1){
//								moveStraight(enemyblue[i],1,tickCount5,-200,156,26 - 20*i,156);
//							}else{
//								if(tickCount5 >= 10*i && tickCount5 < 50+ 10*i){
//									moveStraight(enemyblue[i],1,tickCount5 - 10,26 - 20*i,156,194,156);
//									}
//								else if(tickCount5 >= 50+ 10*i && tickCount5 < 100 + 10*i){
//									moveStraight(enemyblue[i],1,tickCount5 - 60,194,156,110,27);
//									}
//								else{
//									moveStraight(enemyblue[i],1,tickCount5 - 110,110,27,26,156);
//								if(tickCount5 == 150 + 10*i -1) tickCount5 = 0;
//								}
//							}
//					}
//						start = 0;
//					}
//	Round 7
//		if(redenemys == 9){
//			for(int16_t i = 0 ; i < 1 ;i++){
//			enemyorange[i].setVisible(true);
//			orangelazer[i].setVisible(true);
//			isActive[i]=1;
//			}
//		}
//
//		if(redenemys >= 9){
//			if (tickCount7 == 100)  tickCount7 == 0;
//	        tickCount7+=1;
//			for(int16_t i = 0 ; i < 1 ;i++){
//				if (tickCount7 <= 50) moveStraight(enemyorange[i],1,tickCount7,240,60,160,60);
//				else {
//					int16_t x = enemyorange[i].getX(), y = enemyorange[i].getY(), z = 50*sqrt((x-110)*(x-110)+(y-60)*(y-60));
//	            	moveStraight(enemyorange[i],1,(tickCount7-50),x,y,x+(x-110)/z,y+(y-60)/z);
//				}
//	        }
//		}
	//Round 8
	if (redenemys == 32) {
		for (int16_t i = 0; i < 9; i++) {
			enemyblue[i].setVisible(true);
			bluelazer[i].setVisible(true);
			isActiveBlue[i] = 1;
		}
	}
	if (redenemys >= 32) {
		tickCount8 += 1;
		for (int16_t i = 0; i < 9; i++) {
			moveStraight(enemyblue[i], 1, tickCount8, i * (20 + 7.5), -20,
					i * (20 + 7.5), 340);
			if (enemyblue[i].getY() > 330)
				tickCount8 = 0;

		}
	}
	//
	//Control player
	control(playerShip,rightButton,leftButton);

	if (redenemys == 41) {
		application().gotoScreen5ScreenSlideTransitionEast();
	}

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
