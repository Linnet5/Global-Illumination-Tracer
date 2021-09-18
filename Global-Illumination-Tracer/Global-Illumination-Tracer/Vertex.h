#pragma once
#include "Vec3.h"
class Vertex
{
	private:
		Vec3 cords;
		const double w = 1;


	public:
		Vertex();
		Vertex(double inX, double inY, double inZ);
		Vertex(Vec3 inVec);
		void operator=(const Vertex& other);
		Vertex operator-(Vertex& other);
		Vec3 getCords();
		double getX();
		double getY();
		double getZ();

};

