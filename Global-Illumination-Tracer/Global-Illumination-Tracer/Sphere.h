#pragma once
#include "Shapes.h"
class Sphere : public Shapes{   
   
	public:
		glm::vec3 center;
		float radius;
		ColorDbl color;
		Material material; 
	
		Sphere();
		bool renderFunction(Ray& renderRay, glm::vec3 direction);
		

};

