#include "Pixel.h"

Pixel::Pixel() {
	color = ColorDbl(0, 0, 0);
}

void Pixel::setRay(Ray* inRay)
{
	refRay = inRay;
}

void Pixel::setColor(ColorDbl inColor)
{
	color = inColor;
}


