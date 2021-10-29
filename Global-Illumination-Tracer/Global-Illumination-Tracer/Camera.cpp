#include "Camera.h"
#include "Sphere.h" //Forward declared in Ray

int x = 0;
int y = 0;
Camera::Camera() {
	eye0 = glm::vec3(-2, 0, 0);
	eye1 = glm::vec3(-1, 0.0, 0);
	eye2 = glm::vec3(0, 0, 0);
}

void Camera::render() {
	
	auto pixels = new Pixel[800][800];
	double maxR = 0, maxG = 0, maxB = 0;
	BMP outImage;
	outImage.SetSize(800, 800);
	gen = std::mt19937(rd());
	dis = std::uniform_real_distribution<float>(0, 1);
	dis3 = std::uniform_real_distribution<float> (0, 3);

	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			glm::vec3 pixelPosition = glm::vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			glm::vec3 totalColor = glm::vec3(0,0,0);
			int raysPerPixel = 50;
			for (int k = 0; k < raysPerPixel; k++) {
				totalColor += renderEquation(eye1, glm::normalize(pixelPosition - eye1));
			}
			pixels[i, j]->setColor(totalColor/raysPerPixel);

			if (glm::sqrt(pixels[i, j]->color.GetValues().x) > maxR)
				maxR = glm::sqrt(pixels[i, j]->color.GetValues().x);
			if (glm::sqrt(pixels[i, j]->color.GetValues().y) > maxG)
				maxG = glm::sqrt(pixels[i, j]->color.GetValues().y);
			if (glm::sqrt(pixels[i, j]->color.GetValues().z) > maxB)
				maxB = glm::sqrt(pixels[i, j]->color.GetValues().z);
			

			outImage(i, j)->Red = pixels[i, j]->color.GetValues().x;
			outImage(i, j)->Green = pixels[i, j]->color.GetValues().y;
			outImage(i, j)->Blue = pixels[i, j]->color.GetValues().z;
			outImage(i, j)->Alpha = 1;
		}
	}

	truncate(outImage, maxR, maxG, maxB);
	std::cout << maxR << " " << maxG << " " << maxB << std::endl;

	std::cout << outImage.WriteToFile("nuts.bmp");
	delete[] pixels;
}

glm::vec3 Camera::renderEquation(glm::vec3 start, glm::vec3 direction) {
	Ray renderRay = Ray(start, direction, glm::vec3(0, 0, 0));
	bool touchedObj = false;

	glm::vec3 brdf = glm::vec3(0, 0, 0);
	glm::vec3 radiance;
	for (int obj = 0; obj < 2; obj++) {
		if (scene.objects[obj]->renderFunction(renderRay, direction)) {

			touchedObj = true;
		}
	}

	//Only render room for the pixels that are not already filled with object pixels
	if (!touchedObj) {
		for (int tri = 0; tri < 24; tri++) {
			//can be improved by letting you switch eye
			if (scene.room[tri].mollerTrumbore(renderRay.start, direction, renderRay.end, renderRay.tDistance)) {
				renderRay.endPointTriangle = &scene.room[tri];
				if (tri == 5) {
					if (scene.lightList[0].renderFunction(renderRay, direction)) {
						return(glm::vec3(255, 255, 255)); 
					}

				}
			}
		}
	}	
	
	if (renderRay.endPointTriangle != nullptr) {
		float reflectance = renderRay.endPointTriangle->material.reflectance;
		glm::vec3 normal = renderRay.endPointTriangle->calculateNormal();
		if (reflectance < 1) {	
			glm::vec3 albedo = ((renderRay.endPointTriangle->color.GetValues() / 255.0f) * reflectance);
			//return directRadiance(renderRay, albedo, normal);
			return lambertianReflector(renderRay, albedo, reflectance, normal);
		}
		else{
			return mirrorReflector(renderRay, normal);
		}
	}
	
	else if (renderRay.endPointSphere != nullptr) {
		float reflectance = renderRay.endPointSphere->material.reflectance;
		glm::vec3 normal = glm::normalize(renderRay.end - renderRay.endPointSphere->center);
		if (reflectance < 1) {
			glm::vec3 albedo = ((renderRay.endPointSphere->color.GetValues() / 255.0f) * reflectance);
			//return directRadiance(renderRay, albedo, normal);
			return lambertianReflector(renderRay, albedo, reflectance, normal);
		}
		else {
			return mirrorReflector(renderRay, normal);
		}
	}
	else {
		
		std::cout << y << std::endl;
		y++;
	}
	return glm::vec3(0, 0, 0);
	
}

glm::vec3 Camera::lambertianReflector(Ray renderRay, glm::vec3 albedo, float reflectance, glm::vec3 normal)
{
	float rand3 = dis(gen);

	if ((1 - reflectance) < rand3) {

		float rand1 = dis(gen);
		float rand2 = dis(gen);
		

		float theta = (pi * rand1) / 2;
		float azimuth = 2 * pi * rand2;
		
		glm::vec3 outVec = normal;
		glm::vec3 offset = 0.0001f * normal; //behöver nog, udda nog så blev det bättre resulata med - offset, rätt säker att våran tetrahedron har en fucked normal

		glm::vec3 temp = normal + glm::vec3(1, 1, 1);
		glm::vec3 tangent = glm::cross(normal, temp);

		//FIX???
		if (glm::length(tangent) == 0) {
			tangent = normal;
		}

		outVec = glm::rotate(outVec, theta, tangent);// kolla documentation för hur vi gör detta https://glm.g-truc.net/0.9.3/api/a00199.html
		outVec = glm::normalize(glm::rotate(outVec, azimuth, normal));

		glm::vec3 brdf = (albedo *0.8f* cos(theta) * sin(theta) * pi) ;

		glm::vec3 radiance = renderEquation(renderRay.end + offset, outVec);

		glm::vec3 directLight = directRadiance(renderRay, albedo, normal);

		glm::vec3 newRadiance = (radiance * brdf + directLight) / ((reflectance));

		return newRadiance;
	}
	return directRadiance(renderRay, albedo, normal);
}
		

glm::vec3 Camera::mirrorReflector(Ray renderRay, glm::vec3 normal)
{
	glm::vec3 offset = 0.0001f * normal;
	glm::vec3 inDirection = glm::normalize(renderRay.end - renderRay.start);
	glm::vec3 outDirection = inDirection - (2.0f * glm::dot(inDirection, normal) * normal);

	glm::vec3 radiance = renderEquation(renderRay.end + offset, outDirection);
	return radiance;
}

glm::vec3 Camera::directRadiance(Ray renderRay, glm::vec3 albedo, glm::vec3 normal)
{
	glm::vec3 e1 = glm::normalize(scene.lightList[0].edge1);
	glm::vec3 e2 = glm::normalize(scene.lightList[0].edge2); 
	glm::vec3 offset = 0.0001f * normal; 
	Ray dummyRay = Ray(renderRay.end + offset, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	glm::vec3 dirRadiance = glm::vec3(0,0,0);
	int n_samples = 10;
	for (int i = 0; i < n_samples; i++) {
		float c1 = dis(gen);
		float c2 = dis(gen);
		
		bool V = true;

		glm::vec3 randCord = scene.lightList[0].tris[0].getVertex(0).getCords() + c1 * e1 + c2 * e2;
		glm::vec3 shadowRay = randCord - renderRay.end;
		glm::vec3 shadowRayDirection = glm::normalize(shadowRay);
		
		for (int obj = 0; obj < 2; obj++) {
			if (scene.objects[obj]->renderFunction(dummyRay, shadowRayDirection)) {
				//if (dummyRay.endPointTriangle == renderRay.endPointTriangle) { std::cout << "d"; }
					V = false;
			}
		} 
		//std::cout << glm::dot(-1.0f * shadowRay, glm::cross(e1, e2)) << " " << glm::dot(shadowRay, glm::normalize(renderRay.endPointTriangle->calculateNormal())) << std::endl;
		if (V) {	
			float G = (glm::dot(-1.0f * shadowRay,glm::cross(e1, e2)) / glm::length(shadowRay)) * (glm::dot(shadowRay, normal) / glm::length(shadowRay)); 
			G /= glm::dot(shadowRay, shadowRay);
			dirRadiance += (G * glm::length((glm::cross(scene.lightList[0].edge1, scene.lightList[0].edge2)) * glm::vec3(255, 255, 255) * 6));
			//if (G < -0.01) std::cout << glm::to_string(shadowRadiance);
		}
	}
	dirRadiance =  (dirRadiance * albedo)  / (pi * n_samples);
	//std::cout << glm::to_string(albedo) << std::endl;
	//std::cout << glm::to_string(shadowRadiance) << std::endl;

	return dirRadiance;
	
	//std::cout << (factor * shadowRadiance).x << " " << (factor * shadowRadiance).y << " " << (factor * shadowRadiance).z << " " << std::endl;
	//return factor * shadowRadiance;
}

void Camera::truncate(BMP& image, const double maxR, const double maxG, const double maxB)
{
	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			image(i, j)->Red = glm::sqrt(image(i, j)->Red) * (255.99 / maxR);
			image(i, j)->Green = glm::sqrt(image(i, j)->Green) * (255.99 / maxG);
			image(i, j)->Blue = glm::sqrt(image(i, j)->Blue) * (255.99 / maxB);
		}
	}
}

/*
void Camera::createImage(Pixel pixels[800][800], double maxR, double maxG, double maxB){

	//Create BMP file
	BMP outImage;
	outImage.SetSize(800, 800);
	
	for (int i = 0; i < 800; i++){
		for(int j = 0; j < 800; j++){
			outImage(i, j)->Red = pixels[i, j]->color.GetValues().x();
			outImage(i, j)->Green = pixels[i, j]->color.GetValues().y();
			outImage(i, j)->Blue = pixels[i, j]->color.GetValues().z();
			outImage(i, j)->Alpha = 1;
		}
	}
	std::cout << outImage.WriteToFile("nuts.bmp");

}
*/

