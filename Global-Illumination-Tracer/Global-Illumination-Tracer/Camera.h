#pragma once
#include "Pixel.h"
#include "Ray.h"
#include "Triangle.h"
#include <vector>
#include "Scene.h"
#include "EasyBMP.h"
#include <random>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"

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
		std::uniform_real_distribution<float> dis;
		const float pi = 3.14159265358979323846;

		//Pixel pixelArray = new Pixel [800][800];

		Camera();
		void render();
		void truncate(BMP& image, const double maxR, const double maxG, const double maxB);
		glm::vec3 renderEquation(glm::vec3 start, glm::vec3 direction, Ray oldRay);
		
		//void createImage(Pixel pixels[800][800], double maxR, double maxG, double maxB);
};

