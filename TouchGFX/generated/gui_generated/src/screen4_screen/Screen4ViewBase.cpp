/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen4_screen/Screen4ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

Screen4ViewBase::Screen4ViewBase()
{

    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    background.setPosition(1, 0, 240, 320);
    background.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    background.setAlpha(99);

    playerShip.setBitmap(touchgfx::Bitmap(BITMAP_SHIP_ID));
    playerShip.setPosition(105, 265, 31, 36);
    playerShip.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    bullet.setXY(144, -23);
    bullet.setBitmap(touchgfx::Bitmap(BITMAP_BULLET_ID));

    enemy.setXY(61, -24);
    enemy.setBitmap(touchgfx::Bitmap(BITMAP_ENEMY_ID));

    scalableImage1.setBitmap(touchgfx::Bitmap(BITMAP_HP_ID));
    scalableImage1.setPosition(0, 4, 105, 23);
    scalableImage1.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    hpplayer.setBitmap(touchgfx::Bitmap(BITMAP_HP_PLAYER_ID));
    hpplayer.setPosition(10, 11, 85, 9);
    hpplayer.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    enemybullet.setXY(46, 320);
    enemybullet.setBitmap(touchgfx::Bitmap(BITMAP_ENEMYBULLET_ID));

    bosslazer.setXY(240, 113);
    bosslazer.setBitmaps(BITMAP_GIPHY_0_ID, BITMAP_GIPHY_2_ID);
    bosslazer.setUpdateTicksInterval(1);
    bosslazer.startAnimation(false, true, true);

    enemyblueO.setXY(17, -27);
    enemyblueO.setBitmap(touchgfx::Bitmap(BITMAP_ENEMYBLE_ID));

    enemyorangeO.setXY(366, 314);
    enemyorangeO.setBitmap(touchgfx::Bitmap(BITMAP_ENEMYORANGE_ID));

    bluelazerO.setXY(113, 320);
    bluelazerO.setBitmap(touchgfx::Bitmap(BITMAP_BLUELAZER_ID));

    orangelazerO.setXY(189, 320);
    orangelazerO.setBitmap(touchgfx::Bitmap(BITMAP_ORANGELZER_ID));

    image1.setXY(176, -21);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_HEAL_ID));

    x3.setXY(101, -21);
    x3.setBitmap(touchgfx::Bitmap(BITMAP_X3_ID));

    explore.setXY(241, 166);
    explore.setBitmaps(BITMAP_EXPLORE1_ID, BITMAP_EXPLORE2_ID);
    explore.setUpdateTicksInterval(1);
    explore.startAnimation(false, true, true);

    leftButton.setDelay(1);
    leftButton.setInterval(60);
    leftButton.setBoxWithBorderPosition(0, 0, 120, 320);
    leftButton.setBorderSize(5);
    leftButton.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    leftButton.setPosition(1, 0, 120, 320);
    leftButton.setAlpha(0);

    rightButton.setDelay(1);
    rightButton.setInterval(60);
    rightButton.setBoxWithBorderPosition(0, 0, 120, 320);
    rightButton.setBorderSize(5);
    rightButton.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    rightButton.setPosition(121, 0, 120, 320);
    rightButton.setAlpha(0);

    add(__background);
    add(background);
    add(playerShip);
    add(bullet);
    add(enemy);
    add(scalableImage1);
    add(hpplayer);
    add(enemybullet);
    add(bosslazer);
    add(enemyblueO);
    add(enemyorangeO);
    add(bluelazerO);
    add(orangelazerO);
    add(image1);
    add(x3);
    add(explore);
    add(leftButton);
    add(rightButton);
}

void Screen4ViewBase::setupScreen()
{

    //endgame
    //When screen transition begins change screen to Screen3
    //Go to Screen3 with screen transition towards East
    application().gotoScreen3ScreenSlideTransitionEast();

    //boss
    //When screen transition begins change screen to Screen5
    //Go to Screen5 with screen transition towards East
    application().gotoScreen5ScreenSlideTransitionEast();

}
