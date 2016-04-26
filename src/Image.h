#ifndef IMAGE_H
#define IMAGE_H

#ifdef _WIN32
#define M_PI PI
#endif

#include "ofMain.h"
#include "Shapes2d/Object2D.h"
#include <math.h>
#include <stdlib.h>

class Image: public Object2D
{
public:
	Image(string imageName);
    void        SetImageName(string imageName);
    string      GetImageName();
    void Create(int x1, int y1, int width, int height, bool isXInverted = false, bool isYInverted = false){}
	static ofImage Blur(ofImage _image);
	static ofImage Sharpen(ofImage _image);;
	static ofImage Edge(ofImage _image);;
	static ofImage Emboss(ofImage _image);;
private:

    string      imgName;
    ofImage     image;

    bool        valueInRange(int value, int min, int max){ return (value >= min) && (value <= max); }
    double      dotProduct(const ofPoint & point1, const ofPoint & point2);
    void drawShape();
	void refreshPoints() {}
	static ofImage applyFilter(ofImage _image, ofMatrix3x3 _kernel);

};

#endif // IMAGE_H
