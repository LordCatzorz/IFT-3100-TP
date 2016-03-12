#ifndef SCREENSHOTMANAGER_H
#define SCREENSHOTMANAGER_H

class ScreenshotManager
{
public:
    static void TakeScreenshot(string name, int x, int y, int width, int height){
        ofImage screenImg;
        screenImg.allocate(width, height, OF_IMAGE_COLOR);
        screenImg.grabScreen(x, y, width, height);
        screenImg.saveImage(name + ".png");
    }
};

#endif // SCREENSHOTMANAGER_H
