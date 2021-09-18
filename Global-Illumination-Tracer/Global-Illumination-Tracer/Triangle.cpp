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


Direction Triangle::calculateNormal(){
	
	 Vertex u = v1 - v0; 
	 Vertex v = v2 - v0;
	 Vec3 temp;
	 return (Direction (temp.cross(u.getCords(),v.getCords())));
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

bool Triangle::mollerTrumbore(Vec3 rayOrigin, Vec3 rayDirection, Vec3& intersectionPoint) {
	const double EPSILON = 0.0000001;
	Vec3 edge1, edge2, P, T, Q;
	double a, f, u, v, t;

	edge1 = v1.getCords() - v0.getCords();
	edge2 = v2.getCords() - v0.getCords();

	P = P.cross(rayDirection, edge2); // behövs = ? kan vara fel källa :)
	a = edge1.dot(edge1, P);
	if (a > -EPSILON && a < EPSILON) return false; //parallel

	f = 1.0 / a;
	T = rayOrigin - v0.getCords();
	u = f * T.dot(T, P);
	if (u < 0.0 || u > 1.0) return false; //utanför triangel enligt barycentric cords

	Q = Q.cross(T, edge1);
	v = f * rayDirection.dot(rayDirection, Q);
	if (v < 0.0 || u + v > 1.0) return false; //utanför triangel enligt barycentric cords

	t = f * edge2.dot(edge2, Q);
	if (t > EPSILON) {
		intersectionPoint = rayOrigin + rayDirection * t;
		return true;
	}

	else {
		return false; 
	}

}
