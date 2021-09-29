#include "Camera.h"

Camera::Camera() {
	eye0 = Vec3(-2, 0, 0);
	eye1 = Vec3(-1, 0, 0);
	eye2 = Vec3(0, 0, 0);
}

void Camera::render() {
	
	Vec3 dummy = Vec3(0, 0, 0);

	auto pixels = new Pixel[800][800];
	double maxR = 0, maxG = 0, maxB = 0;
	BMP outImage;
	outImage.SetSize(800, 800);

	gen = std::mt19937(rd());
	dis = std::uniform_real_distribution<double>(0, 1);

	std::cout << dis(gen);


	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			Vec3 pixelPosition = Vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			Ray renderRay = Ray(eye1.getCords(), dummy, ColorDbl(Vec3(0, 0, 0)));
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
					}
				}
			}
				pixels[i, j]->setRay(&renderRay);
				if (pixels[i, j]->refRay->endPointTriangle != nullptr) {
					pixels[i, j]->setColor(ColorDbl(pixels[i, j]->refRay->endPointTriangle->color.GetValues().x(), pixels[i, j]->refRay->endPointTriangle->color.GetValues().y(), pixels[i, j]->refRay->endPointTriangle->color.GetValues().z()));

					//Fetches max color value in the scene for each color channel
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().x() > maxR)
						maxR = pixels[i, j]->refRay->endPointTriangle->color.GetValues().x();
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().y() > maxG)
						maxG = pixels[i, j]->refRay->endPointTriangle->color.GetValues().y();
					if (pixels[i, j]->refRay->endPointTriangle->color.GetValues().z() > maxB)
						maxB = pixels[i, j]->refRay->endPointTriangle->color.GetValues().z();
			}

			//Fills the out image with the values of the pixels array
			outImage(i, j)->Red = pixels[i, j]->color.GetValues().x();
			outImage(i, j)->Green = pixels[i, j]->color.GetValues().y();
			outImage(i, j)->Blue = pixels[i, j]->color.GetValues().z();
			outImage(i, j)->Alpha = 1;
		}
	}

	truncate(outImage, maxR, maxG, maxB);

	//createImage(pixels, maxR, maxG, maxB);
	std::cout << outImage.WriteToFile("nuts.bmp");
	delete[] pixels;
}

Vec3 Camera::renderEquation(Vec3 start, Vec3 direction) {
	Ray renderRay = Ray(start, direction, Vec3(0, 0, 0));
	bool touchedObj = false;
	bool lightSourceTouched = false;
	Vec3 radiance;
	for (int obj = 0; obj < 1; obj++) {
		if (scene.objects[obj]->renderFunction(renderRay, direction)) {
			touchedObj = true;
		}
	}

	//Only render room for the pixels that are not already filled with object pixels
	if (!touchedObj) {
		for (int tri = 0; tri < 24; tri++) {
			//can be improved by letting you switch eye
			if (scene.room[tri].mollerTrumbore(renderRay.start, direction - renderRay.start, renderRay.end)) {
				if (tri == 3) {
					lightSourceTouched = true;
				}
				renderRay.endPointTriangle = &scene.room[tri];
			}
		}
	}
	
	const int nSamples = 1;
	for (int i = 0; i < nSamples; i++) {
		double rand1 = dis(gen);
		double rand2 = dis(gen);
		double rand3 = dis(gen);

		double theta = (pi * rand1) / 2;
		double azimuth = 2 * pi * rand2;

		
		//all disepation coditions
		if (!lightSourceTouched /* || (1 - endPointTrianlge.lambertianReflectance) < rand3 */) {
			//Vec3 newDirection  = renderRay.endPointTriangle."HUR VI RÄKNAR NU NORMALEN";
			//newDirection = glm::rotate(inclination); kolla documentation för hur vi gör detta https://glm.g-truc.net/0.9.3/api/a00199.html
			//newDirection = glm::rotate(azimuth);

			//radianceCoeficence = (M_PI * endPointTrianlge.lambertianReflectance * cos(incline) * sin(incline))/( 1 - endPointTrianlge.lambertianReflectance);

			//radiance = renderEquation(renderRay.end, newDirection, renderRay);
		}
		else if (lightSourceTouched) {
			radiance = Vec3(1.0, 1.0, 1.0); //eller vad L0 är
		}

		//Vec3 newRadiance = radiance * radianceCoeficence  + functionSomRäknarShadowRay(renderRay.start); //kanske problem att den klagar på radiance inte har värde för alla decs av readiance är i if satser.
		//return newRadiance;
		return Vec3(0, 0, 0);

	}

	
	
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