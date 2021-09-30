#pragma once
#include "glm/glm.hpp"

class Vertex
{
	private:
		glm::vec3 cords;
		const double w = 1;

	public:
		Vertex();
		Vertex(double inX, double inY, double inZ);
		Vertex(glm::vec3 inVec);
		void operator=(const Vertex& other);
		Vertex operator-(Vertex& other);
		glm::vec3 getCords();
		double getX();
		double getY();
		double getZ();

};

