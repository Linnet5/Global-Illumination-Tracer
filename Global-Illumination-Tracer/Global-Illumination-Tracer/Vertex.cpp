#include "Vertex.h"

//Def constructor
Vertex::Vertex() {
	cords = glm::vec3(0, 0, 0);
}

Vertex::Vertex(double inX, double inY, double inZ){
	cords = glm::vec3(inX, inY, inZ);
}

Vertex::Vertex(glm::vec3 inVec){
	cords = inVec;
}

//Copy operator overload
void Vertex::operator=(const Vertex& other) {
	cords = other.cords;
}


Vertex Vertex::operator-(Vertex& other) {
	Vertex temp = cords - other.cords;
	return temp;
}

glm::vec3 Vertex::getCords() {
	return cords;
}

double Vertex::getX() {
	return cords.x;
}

double Vertex::getY() {
	return cords.y;
}

double Vertex::getZ() {
	return cords.z;
}

