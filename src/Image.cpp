#include "Image.h"
#include <cmath>

Image::Image(string imageName)
{
	imgName = imageName;
	image.load(imgName);
	image.allocate(image.getWidth(), image.getHeight(), OF_IMAGE_COLOR);

	topLeftPoint.x = 0;
	topLeftPoint.y = 0;
	topRightPoint.x = image.getWidth();
	topRightPoint.y = 0;
	bottomLeftPoint.x = 0;
	bottomLeftPoint.y = image.getHeight();
	bottomRightPoint.x = image.getWidth();
	bottomRightPoint.y = image.getHeight();
	refreshBorders();
}

void Image::SetImageName(string imageName)
{
	image.load(imgName);

	topRightPoint.x = topLeftPoint.x + image.getWidth();
	bottomLeftPoint.y = topLeftPoint.y + image.getHeight();
	bottomRightPoint.x = topLeftPoint.x + image.getWidth();
	bottomRightPoint.y = topLeftPoint.y + image.getHeight();
	refreshBorders();
}

string Image::GetImageName()
{
	return imgName;
}

ofImage Image::Blur(ofImage _image)
{
	ofMatrix3x3 mat = ofMatrix3x3(1, 1, 1, 1, 1, 1, 1, 1, 1);
	return applyFilter(_image, mat);
}

ofImage Image::Sharpen(ofImage _image)
{
	ofMatrix3x3 mat = ofMatrix3x3(0, -1, 0, -1, 5, -1, 0, -1, 0);
	return applyFilter(_image, mat);
}

ofImage Image::Edge(ofImage _image)
{
	ofMatrix3x3 mat = ofMatrix3x3(0, 1, 0, 1, -4, 1, 0, 1, 0);
	return applyFilter(_image, mat);
}

ofImage Image::Emboss(ofImage _image)
{
	ofMatrix3x3 mat = ofMatrix3x3(-2, -1, 0, -1, 1, 1, 0, 1, 2);
	return applyFilter(_image, mat);
}

ofImage Image::applyFilter(ofImage _image, ofMatrix3x3 _kernel)
{
	int width = _image.getWidth();
	int height = _image.getHeight();
	float sumKernel = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sumKernel += ABS(_kernel[i * 3 + j]);
		}
	}
	_kernel = _kernel * (1.0 / sumKernel);

	unsigned char* pixels = _image.getPixels();
	unsigned char* finalPixels = _image.getPixels();
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float r = 0;
			float g = 0;
			float b = 0;
			for (int filterY = -1; filterY <= 1; filterY++)
			{
				for (int filterX = -1; filterX <= 1;filterX++)
				{
					int index = 3*((y + filterY)*width + x + filterX);
					r += pixels[index + 0] * _kernel[(filterY + 1) * 3 + filterX + 1];
					g += pixels[index + 1] * _kernel[(filterY + 1) * 3 + filterX + 1];
					b += pixels[index + 2] * _kernel[(filterY + 1) * 3 + filterX + 1];

				}
            }

			finalPixels[3 * (y*width + x) + 0] = r;
			finalPixels[3 * (y*width + x) + 1] = g;
			finalPixels[3 * (y*width + x) + 2] = b;
		}
	}
	ofImage finalImage = ofImage();
	finalImage.setFromPixels(finalPixels, width, height, ofImageType::OF_IMAGE_COLOR);
	return finalImage;

}

double rotVal = 0;
void Image::drawShape()
{
	ofSetColor(ofColor::white);
	image.allocate(topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y, OF_IMAGE_COLOR);
    image.draw(topLeftPoint.x, topLeftPoint.y, topRightPoint.x - topLeftPoint.x, bottomLeftPoint.y - topLeftPoint.y);
}

double Image::dotProduct(const ofPoint & point1, const ofPoint & point2)
{
	return 0;
}
