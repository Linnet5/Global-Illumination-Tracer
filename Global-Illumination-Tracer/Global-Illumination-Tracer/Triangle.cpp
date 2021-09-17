#include "Triangle.h"

Triangle::Triangle() {
	//Dummy triangle with all vertices at 0,0,0
	v1 = Vertex(0, 0, 0);
	v2 = v1;
	v3 = v1;
}

Triangle::Triangle(Vertex inV1, Vertex inV2, Vertex inV3, ColorDbl inColor) {
	v1 = inV1;
	v2 = inV2;
	v3 = inV3;
	color = inColor;
	dir = calculateNormal();
}


Direction Triangle::calculateNormal(){
	 Vertex u = v2 - v1; 
	 Vertex v = v3 - v1;

	 double tempUx = u.getX();
	 double tempUy = u.getY();
	 double tempUz = u.getZ();
	 double tempVx = v.getX();
	 double tempVy = v.getY();
	 double tempVz = v.getZ();

	 Direction temp((tempUy * tempVz) - (tempUz * tempVy), (tempUz * tempVx) - (tempUx * tempVz), (tempUx * tempVy) - (tempUy * tempVx));
	 return temp;
}