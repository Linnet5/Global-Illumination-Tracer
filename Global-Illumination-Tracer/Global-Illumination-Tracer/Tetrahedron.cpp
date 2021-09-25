#include "Tetrahedron.h"

Tetrahedron::Tetrahedron() {
	sides[0] = Triangle(vertexList[0], vertexList[2], vertexList[1], ColorDbl(227, 242, 160));
	sides[1] = Triangle(vertexList[0], vertexList[3], vertexList[2], ColorDbl(227, 242, 160));
	sides[2] = Triangle(vertexList[0], vertexList[1], vertexList[3], ColorDbl(227, 242, 160));
	sides[3] = Triangle(vertexList[1], vertexList[2], vertexList[3], ColorDbl(227, 242, 160));
}