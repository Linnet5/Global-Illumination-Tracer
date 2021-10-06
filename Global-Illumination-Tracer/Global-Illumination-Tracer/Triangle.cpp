#include "Triangle.h"

Triangle::Triangle() {
	//Dummy triangle with all vertices at 0,0,0
	v0 = Vertex(0, 0, 0);
	v1 = v0;
	v2 = v0;
}

Triangle::Triangle(Vertex inV0, Vertex inV1, Vertex inV2, ColorDbl inColor) {
	v0 = inV0;
	v1 = inV1;
	v2 = inV2;
	color = inColor;
	dir = calculateNormal();
}


glm::vec3 Triangle::calculateNormal(){
	
	 Vertex u = v1 - v0; 
	 Vertex v = v2 - v0;
	 glm::vec3 temp;
	 return glm::normalize(glm::cross(u.getCords(),v.getCords()));
	 /*
	 double tempUx = u.getX();
	 double tempUy = u.getY();
	 double tempUz = u.getZ();
	 double tempVx = v.getX();
	 double tempVy = v.getY();
	 double tempVz = v.getZ();

	 Direction temp((tempUy * tempVz) - (tempUz * tempVy), (tempUz * tempVx) - (tempUx * tempVz), (tempUx * tempVy) - (tempUy * tempVx));
	 return temp; */
}

bool Triangle::mollerTrumbore(glm::vec3 rayOrigin, glm::vec3 rayDirection, glm::vec3& intersectionPoint) {
	const double EPSILON = 0.000000001;
	glm::vec3 edge1, edge2, P, T, Q;
	double a, f, u, v;
	float t;

	edge1 = v1.getCords() - v0.getCords();
	edge2 = v2.getCords() - v0.getCords();

	P = glm::cross(rayDirection, edge2); // behövs = ? kan vara fel källa :)
	a = glm::dot(edge1, P);
	if (a > -EPSILON && a < EPSILON) return false; //parallel

	f = 1.0 / a;
	T = rayOrigin - v0.getCords();
	u = f * glm::dot(T, P);
	if (u < 0.0 || u > 1.0) return false; //utanför triangel enligt barycentric cords

	Q = glm::cross(T, edge1);
	v = f * glm::dot(rayDirection, Q);
	if (v < 0.0 || u + v > 1.0) return false; //utanför triangel enligt barycentric cords

	t = f * glm::dot(edge2, Q);
	if (t > EPSILON) {
		intersectionPoint = rayOrigin + rayDirection * t;
		return true;
	}

	else {
		return false; 
	}

}
