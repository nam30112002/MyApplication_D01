#include <gui/screen2_screen/Screen2View.hpp>
#include "cmsis_os.h"

extern osMessageQueueId_t Queue1Handle;

Screen2View::Screen2View()
{
	tickCount = 0;
}

void Screen2View::setupScreen()
{
	localImageX = presenter->GetImageX();
    Screen2ViewBase::setupScreen();
    image1.setX(localImageX);
    lamb.setX(30);
    lamb.setY(0);
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
    presenter->UpdateImageX(localImageX);
}

void Screen2View::handleTickEvent()
{
	Screen2ViewBase::handleTickEvent();

	tickCount++;

	uint32_t rand[10] = {1,9,8,7,5,6,10,2,4,3};
	uint8_t res = 0 ;
	uint32_t count = osMessageQueueGetCount(Queue1Handle);
    if(count > 0)
    {
    	osMessageQueueGet(Queue1Handle,&res,NULL,osWaitForever);
    	if(res == 'R')
    	{
    		int16_t x = image1.getX();
    		x+=1;
    		if(x>240){
    			x = 0;

    		}
    		image1.setX(x);
    	}
    	if(res == 'L')
    	{
    		int16_t x = image1.getX();
    		x-=1;
    		if(x<0){
    			x = 240;
    		}
    		image1.setX(x);
    	}
    }

	lamb.setY(tickCount*2%320);
	lamb.setX(tickCount*2/320%4*60+15);
	if(lamb.getY()>=134 and lamb.getY()<=229){
		if(lamb.getX()==15){
			if(image1.getX()>=-25 and image1.getX()<=38){
				tickCount--;
				 application().gotoScreen3ScreenSlideTransitionEast();
			}
		}
		if(lamb.getX()==75){
			if(image1.getX()>=34 and image1.getX()<=97){
				tickCount--;
				 application().gotoScreen3ScreenSlideTransitionEast();
			}
		}
		if(lamb.getX()==135){
			if(image1.getX()>=95 and image1.getX()<=158){
				tickCount--;
				 application().gotoScreen3ScreenSlideTransitionEast();
			}
		}
		if(lamb.getX()==195){
			if(image1.getX()>=154 and image1.getX()<=217){
				tickCount--;
				 application().gotoScreen3ScreenSlideTransitionEast();
			}
		}

	}

	invalidate();
}
