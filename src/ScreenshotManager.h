#ifndef SCREENSHOTMANAGER_H
#define SCREENSHOTMANAGER_H
#include "Image.h"
class ScreenshotManager
{
public:
    static void TakeScreenshot(string name, int x, int y, int width, int height, bool blur=false){
        ofImage screenImg;
        screenImg.allocate(width, height, OF_IMAGE_COLOR);
        screenImg.grabScreen(x, y, width, height);
		if (blur)
		{
            screenImg = Image::Blur(screenImg);
		}
        screenImg.saveImage(name + ".png");
        screenImg.clear();
    }
};

#endif // SCREENSHOTMANAGER_H
