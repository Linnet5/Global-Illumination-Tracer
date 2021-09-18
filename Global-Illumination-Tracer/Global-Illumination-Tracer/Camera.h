#pragma once
#include "Pixel.h"
#include "Ray.h"
#include "Triangle.h"
#include <vector>
class Camera
{
	public:
		Vertex eye0, eye1;
		int eyeSwitch = 0;
		//int resolution = 800;

		int cols = 800;
		std::vector<std::vector<Pixel> > pixelArray; 

		//Pixel pixelArray = new Pixel [800][800];

		Camera();
		void render();
};

