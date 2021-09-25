#include "Tetrahedron.h"

Tetrahedron::Tetrahedron() {
	sides[0] = Triangle(vertexList[0], vertexList[2], vertexList[1], ColorDbl(227, 242, 160));
	sides[1] = Triangle(vertexList[0], vertexList[3], vertexList[2], ColorDbl(227 * 0.8, 242 * 0.8, 160 * 0.8));
	sides[2] = Triangle(vertexList[0], vertexList[1], vertexList[3], ColorDbl(227 * 0.6, 242 * 0.6, 160 * 0.6));
	sides[3] = Triangle(vertexList[1], vertexList[2], vertexList[3], ColorDbl(227 * 0.4, 242 * 0.4, 160 * 0.4));
}

bool Tetrahedron::renderFunction (Ray& renderRay, Vec3 direction)
{
	Vec3 t = Vec3(999, 999, 999);
	bool flag = false;
	for (int tri = 0; tri < 4; tri++) {
		if(sides[tri].mollerTrumbore(renderRay.start, direction - renderRay.start, renderRay.end)){
			if((renderRay.end - renderRay.start).length() < t.length()){
				renderRay.endPointTriangle = &sides[tri];
				t = renderRay.end;
				flag = true;
			}
		}
	}
	return flag;
}
