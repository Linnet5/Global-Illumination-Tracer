#pragma once
#include "ColorDbl.h"
#include "Ray.h"
class Pixel
{
	public:
		ColorDbl color;
		Ray* refRay;

		Pixel();
		void setRay(Ray* inRay);
		void setColor(ColorDbl inColor);


};

