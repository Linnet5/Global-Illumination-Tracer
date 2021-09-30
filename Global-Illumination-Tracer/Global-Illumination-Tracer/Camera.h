#pragma once
#include "Pixel.h"
#include "Ray.h"
#include "Triangle.h"
#include <vector>
#include "Scene.h"
#include "EasyBMP.h"
#include <random>

class Camera
{
	public:
		Vertex eye0, eye1, eye2;
		int eyeSwitch = 0;
		Pixel pixels;

		int cols = 800;
		std::vector<std::vector<Pixel> > pixelArray; 
		Scene scene;

		std::random_device rd;
		std::mt19937 gen;
		std::uniform_real_distribution<double> dis;
		const double pi = 3.14159265358979323846;

		//Pixel pixelArray = new Pixel [800][800];

		Camera();
		void render();
		void truncate(BMP& image, const double maxR, const double maxG, const double maxB);
		Vec3 renderEquation(Vec3 start, Vec3 direction);
		
		//void createImage(Pixel pixels[800][800], double maxR, double maxG, double maxB);
};

