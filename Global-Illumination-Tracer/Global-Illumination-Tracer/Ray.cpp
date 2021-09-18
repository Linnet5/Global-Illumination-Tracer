#include "Ray.h"

Ray::Ray(const Vertex& inStart, const Vertex& inEnd, ColorDbl inColor) {
	start = inStart;
	end = inEnd;
	color = inColor;
	endPointTriangle = nullptr; //yikes
}

void Ray::setTriangle(Triangle* triangle){
	endPointTriangle = triangle;
}

