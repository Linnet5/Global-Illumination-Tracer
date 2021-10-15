#include "Sphere.h"

Sphere::Sphere()
{
	center = glm::vec3(4.0f, 1.0f, 0.0f);
	radius = 1.0f;
	color = ColorDbl(0, 255, 255);
	material = Material(0.5f);
}

bool Sphere::renderFunction(Ray& renderRay, glm::vec3 direction)
{
	bool flag = false;
	float b = glm::dot(2.0f * direction, (renderRay.start - center));
	float c = dot((renderRay.start - center), (renderRay.start - center)) - glm::dot(radius, radius);

	//PQ-tecken
	for (int i = -1; i < 2; i = i + 2) {
		float d = -(b / 2.0f) + i * glm::sqrt(glm::pow(b / 2.0f, 2) - c);

		if (d > 0 && d < renderRay.tDistance) {
			renderRay.tDistance = d;
			renderRay.end = renderRay.start + d * direction;
			renderRay.endPointTriangle = nullptr;
			renderRay.endPointSphere = true;
			renderRay.center = center;
			renderRay.radius = radius;
			renderRay.sphereColor = color;
			renderRay.sphereReflectance = material.reflectance;
			flag = true;
		}
	}
	return flag;
}