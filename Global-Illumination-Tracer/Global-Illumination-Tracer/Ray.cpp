#include "Ray.h"

Ray::Ray(const Vertex& inStart, const Vertex& inEnd, ColorDbl inColor) {
	start = inStart;
	end = inEnd;
	color = inColor;
}

void Ray::setTriangle(Triangle& triangle){
	endPointTriangle = triangle;
}

