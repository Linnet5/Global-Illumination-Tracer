#include "Vertex.h"

//Def constructor
Vertex::Vertex() {
	x = 0;
	y = 0;
	z = 0;
}

Vertex::Vertex(double inX, double inY, double inZ){
	x = inX;
	y = inY;
	z = inZ;
}

//Copy operator overload
Vertex Vertex::operator=(const Vertex& other) {
	x = other.x;
	y = other.y;
	z = other.z; 
}

Vertex Vertex::operator-(const Vertex& other) {
	return Vertex(x - other.x, y - other.y, z - other.z);
}

double Vertex::getX() {
	return x;
}

double Vertex::getY() {
	return y;
}

double Vertex::getZ() {
	return z;
}

