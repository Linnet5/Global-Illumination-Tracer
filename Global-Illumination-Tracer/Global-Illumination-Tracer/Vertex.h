#pragma once
class Vertex
{
	private:
		double x;
		double y;
		double z;
		const double w = 1;


	public:
		Vertex();
		Vertex(double inX, double inY, double inZ);
		Vertex operator=(const Vertex& other);
		Vertex operator-(const Vertex& other);
		double getX();
		double getY();
		double getZ();

};

