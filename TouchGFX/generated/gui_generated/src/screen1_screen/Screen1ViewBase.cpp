/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <BitmapDatabase.hpp>

Screen1ViewBase::Screen1ViewBase() :
    buttonCallback(this, &Screen1ViewBase::buttonCallbackHandler)
{

    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    scalableImage1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    scalableImage1.setPosition(0, 0, 240, 320);
    scalableImage1.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);

    button1.setXY(69, 258);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_PLAYBUTTON_ID), touchgfx::Bitmap(BITMAP_PLAYBUTTON_ID));
    button1.setAction(buttonCallback);

    image1.setXY(20, 81);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_LOGO_ID));

    add(__background);
    add(scalableImage1);
    add(button1);
    add(image1);
}

void Screen1ViewBase::setupScreen()
{

}

void Screen1ViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction2
        //When button1 clicked change screen to Screen4
        //Go to Screen4 with screen transition towards East
        application().gotoScreen4ScreenCoverTransitionEast();
    }
}
