#include "LightSource.h"

LightSource::LightSource() {
	//Arbitrary default constructor
	intensity = 1;
	tris[0] = Triangle(Vertex(0, 0, 0), Vertex(0, 0, 0), Vertex(0, 0, 0), ColorDbl(255, 255, 255), Material(0.5));
	tris[1] = Triangle(Vertex(0, 0, 0), Vertex(0, 0, 0), Vertex(0, 0, 0), ColorDbl(255, 255, 255), Material(0.5));

	edge1 = glm::vec3(0,0,0);
	edge2 = glm::vec3(0,0,0);
}

LightSource::LightSource(Vertex v0, Vertex v1, Vertex v2, Vertex v3, double inIntensity)
{
	intensity = inIntensity;
	tris[0] = Triangle(v0, v1, v2, ColorDbl(255, 255, 255), Material(0.5f));
	tris[1] = Triangle(v3, v2, v1, ColorDbl(255, 255, 255), Material(0.5f)); 

	edge1 = v1.getCords() - v0.getCords();
	edge2 = v2.getCords() - v0.getCords();
}

bool LightSource::renderFunction(Ray& renderRay, glm::vec3 direction) {

	bool flag = false;
	for (int tri = 0; tri < 2; tri++) {
		if ((tris[tri].mollerTrumbore(renderRay.start, direction, renderRay.end, renderRay.tDistance))) {
			renderRay.endPointTriangle = &tris[tri];
			flag = true;
			}
		}
	return flag;
}
