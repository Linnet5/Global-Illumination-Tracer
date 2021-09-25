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

Vec3 Camera::renderEquation(Vec3 start, Vec3 direction, Ray oldRay) {
	Ray renderRay = Ray(start, direction, Vec3(0, 0, 0));
	bool touchedObj = false;
	bool lightSourceTouched = false;
	Vec3 Radiance;
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
	//int angleOut = angleIn(renderRay.endPointTriangle);
	//Vec3 newDirection = någonFunktionSomCalcarUtifrånVinkeln(angleout)
	//all disepation coditions
	if (!lightSourceTouched) {  
		//Radiance = renderEquation(renderRay.end, newDirection, renderRay);
	}
	else {
		Vec3 radiance = Vec3(1.0, 1.0, 1.0); //eller vad L0 är
	}
	//Vec3 newRadiance = radiance * functionSomGörF(angle, oldRay.endPointTriangle) /*tror vi behöver oldray för att veta vart strålen är påväg här*/ + functionSomRäknarShadowRay(oldRay.endPointTriangle);
	//return newRadiance;
	return Vec3(0, 0, 0);
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