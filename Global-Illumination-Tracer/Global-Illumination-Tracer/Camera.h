#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include "Pixel.h"
#include "Ray.h"
#include "Triangle.h"
#include <vector>
#include "Scene.h"
#include "EasyBMP.h"
#include <random>
#include "glm/glm.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/ext.hpp"

class Camera
{
	public:
		glm::vec3 eye0, eye1, eye2;
		int eyeSwitch = 0;
		Pixel pixels;

		int cols = 800;
		std::vector<std::vector<Pixel> > pixelArray; 
		Scene scene;

		std::random_device rd;
		std::mt19937 gen;
		std::uniform_real_distribution<float> dis;
		std::uniform_real_distribution<float> dis3;
		const float pi = 3.14159265358979323846;

		//Pixel pixelArray = new Pixel [800][800];

		Camera();
		void render();
		void truncate(BMP& image, const double maxR, const double maxG, const double maxB);
		glm::vec3 renderEquation(glm::vec3 start, glm::vec3 direction);
		glm::vec3 lambertianReflector(Ray renderRay, glm::vec3 albedo, float reflectance, glm::vec3 normal);
		glm::vec3 mirrorReflector(Ray renderRay, glm::vec3 normal);
		glm::vec3 directRadiance(Ray renderRay, glm::vec3 albedo, glm::vec3 normal);
		
		//void createImage(Pixel pixels[800][800], double maxR, double maxG, double maxB);
};

