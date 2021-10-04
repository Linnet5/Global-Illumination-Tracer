#include "Camera.h"

int x = 0;
Camera::Camera() {
	eye0 = glm::vec3(-2, 0, 0);
	eye1 = glm::vec3(-1, -0.5, 0);
	eye2 = glm::vec3(0, 0, 0);
}

void Camera::render() {
	
	glm::vec3 dummy = glm::vec3(0, 0, 0);

	auto pixels = new Pixel[800][800];
	double maxR = 0, maxG = 0, maxB = 0;
	BMP outImage;
	outImage.SetSize(800, 800);

	gen = std::mt19937(rd());
	dis = std::uniform_real_distribution<float>(0, 1);

	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			glm::vec3 pixelPosition = glm::vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			Ray renderRay = Ray(eye1, dummy, ColorDbl(glm::vec3(0, 0, 0)));

			pixels[i, j]->setColor(renderEquation(eye1, pixelPosition - eye1, renderRay));
			/* TEMPORÄRT UTKOMMENTERAD
			glm::vec3 pixelPosition = glm::vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			Ray renderRay = Ray(eye1.getCords(), dummy, ColorDbl(glm::vec3(0, 0, 0)));
			//Vec3 temp = pixelposition - renderRay.start;
			//std::cout << temp.x() << " " << temp.y() << " " << temp.z() << std::endl;
			bool touchedObj = false;
			for (int obj = 0; obj < 1; obj++) {
				if (scene.objects[obj]->renderFunction(renderRay, pixelPosition)) {
				touchedObj = true;
				}
			}

			//Only render room for the pixels that are not already filled with object pixels
			if (!touchedObj) {
				for (int tri = 0; tri < 24; tri++) {
					//can be improved by letting you switch eye
					if (scene.room[tri].mollerTrumbore(renderRay.start, pixelPosition - renderRay.start, renderRay.end)) {
						renderRay.endPointTriangle = &scene.room[tri];
						if (tri == 5) {
							for (int i = 0; i < 2; i++) {
								if (scene.lightSource[i].mollerTrumbore(renderRay.start, pixelPosition - renderRay.start, renderRay.end)) {
									renderRay.endPointTriangle = &scene.lightSource[i];
								}
							}
						}
					}
				}
			}
				pixels[i, j]->setRay(&renderRay);
				if (pixels[i, j]->refRay->endPointTriangle != nullptr) {
					pixels[i, j]->setColor(ColorDbl(pixels[i, j]->refRay->endPointTriangle->color.GetValues().x, pixels[i, j]->refRay->endPointTriangle->color.GetValues().y, pixels[i, j]->refRay->endPointTriangle->color.GetValues().z));

					//Fetches max color value in the scene for each color channel
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().x > maxR)
						maxR = pixels[i, j]->refRay->endPointTriangle->color.GetValues().x;
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().y > maxG)
						maxG = pixels[i, j]->refRay->endPointTriangle->color.GetValues().y;
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().z > maxB)
						maxB = pixels[i, j]->refRay->endPointTriangle->color.GetValues().z;
			}

			//Fills the out image with the values of the pixels array
			outImage(i, j)->Red = pixels[i, j]->color.GetValues().x;
			outImage(i, j)->Green = pixels[i, j]->color.GetValues().y;
			outImage(i, j)->Blue = pixels[i, j]->color.GetValues().z;
			outImage(i, j)->Alpha = 1;
			*/

			if (pixels[i, j]->color.GetValues().x > maxR)
				maxR = pixels[i, j]->color.GetValues().x;
			if (pixels[i, j]->color.GetValues().y > maxG)
				maxG = pixels[i, j]->color.GetValues().y;
			if (pixels[i, j]->color.GetValues().z > maxB)
				maxB = pixels[i, j]->color.GetValues().z;
			

			outImage(i, j)->Red = pixels[i, j]->color.GetValues().x;
			outImage(i, j)->Green = pixels[i, j]->color.GetValues().y;
			outImage(i, j)->Blue = pixels[i, j]->color.GetValues().z;
			outImage(i, j)->Alpha = 1;
		}
	}

	truncate(outImage, maxR, maxG, maxB);

	//createImage(pixels, maxR, maxG, maxB);
	std::cout << outImage.WriteToFile("nuts.bmp");
	delete[] pixels;
}

glm::vec3 Camera::renderEquation(glm::vec3 start, glm::vec3 direction, Ray oldRay) {
	Ray renderRay = Ray(start, direction, glm::vec3(0, 0, 0));
	bool touchedObj = false;
	bool lightSourceTouched = false;
	glm::vec3 bdrf = glm::vec3(0, 0, 0);
	glm::vec3 radiance;
	for (int obj = 0; obj < 1; obj++) {
		if (scene.objects[obj]->renderFunction(renderRay, direction)) {
			touchedObj = true;
		}
	}

	//Only render room for the pixels that are not already filled with object pixels
	if (!touchedObj) {
		for (int tri = 0; tri < 24; tri++) {
			//can be improved by letting you switch eye
			if (scene.room[tri].mollerTrumbore(renderRay.start, direction, renderRay.end)) {
				renderRay.endPointTriangle = &scene.room[tri];
				if (tri == 5) {
					for (int i = 0; i < 2; i++) {
						if (scene.lightSource[i].mollerTrumbore(renderRay.start, direction, renderRay.end)) {
							renderRay.endPointTriangle = &scene.lightSource[i];
							lightSourceTouched = true;
						}
					}
				}
			}
		}
	}
	//std::cout << renderRay.end.x << " " << renderRay.end.y << " " << renderRay.end.z << " " << direction.x << " " << direction.y << " " << direction.z << std::endl;
	x++;
	glm::vec3 albedo = renderRay.endPointTriangle->color.GetValues() * renderRay.endPointTriangle->reflectance;
	const int nSamples = 1;
	for (int i = 0; i < nSamples; i++) {
		float rand1 = dis(gen);
		float rand2 = dis(gen);
		float rand3 = dis(gen);

		float theta = (pi * rand1) / 3;
		float azimuth = 2 * pi * rand2;
		//std::cout << theta << " " << azimuth <<std::endl;

		
		//all disepation coditions
		if (!lightSourceTouched  && (1 - renderRay.endPointTriangle->reflectance) < rand3) {
			glm::vec3 normal = renderRay.endPointTriangle->calculateNormal();
			glm::vec3 outVec = normal;

			glm::vec3 temp = normal + glm::vec3(1, 1, 1);
			glm::vec3 tangent = glm::cross(normal, temp);
			
			outVec = glm::rotate(outVec, theta, tangent);// kolla documentation för hur vi gör detta https://glm.g-truc.net/0.9.3/api/a00199.html
			outVec = glm::rotate(outVec, azimuth, normal);

			glm::vec3 bdrf = (pi * albedo * cos(theta) * sin(theta))/((renderRay.endPointTriangle->reflectance)*nSamples);

			radiance = renderEquation(renderRay.end, normal, renderRay);
		}
		else if (lightSourceTouched) {
			radiance = glm::vec3(1.0, 1.0, 1.0); //eller vad L0 är
		}
		else {
			radiance = glm::vec3(0.0, 0.0, 0.0);
		}

		glm::vec3 newRadiance = radiance * bdrf; // +functionSomRäknarShadowRay(renderRay.start); //kanske problem att den klagar på radiance inte har värde för alla decs av readiance är i if satser.
		return newRadiance;
		

	}

	return glm::vec3(0, 0, 0);
	
}

void Camera::truncate(BMP& image, const double maxR, const double maxG, const double maxB)
{
	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			image(i, j)->Red = image(i, j)->Red * (255.99 / maxR);
			image(i, j)->Green = image(i, j)->Green * (255.99 / maxG);
			image(i, j)->Blue = image(i, j)->Blue * (255.99 / maxB);
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