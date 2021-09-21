#include "Camera.h"

Camera::Camera() {
	eye0 = Vec3(-2, 0, 0);
	eye1 = Vec3(-1, 0, 0);
}

void Camera::render() {
	
	//Create BMP file
	BMP outImage;
	outImage.SetSize(800, 800);
	Vec3 dummy = Vec3(0, 0, 0);

	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			Vec3 pixelposition = Vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			for (int tri = 0; tri < 24; tri++) {
				//can be improved by letting you switch eye
				if (scene.room[tri].mollerTrumbore(eye1.getCords(), pixelposition - eye1.getCords(), dummy)) {
					outImage(i, j)->Red = scene.room[tri].color.GetValues().x();
					outImage(i, j)->Green = scene.room[tri].color.GetValues().y();
					outImage(i, j)->Blue = scene.room[tri].color.GetValues().z();
					outImage(i, j)->Alpha = 1;
				}
			}
		}
	}

	std::cout << outImage.WriteToFile("nuts.bmp");
}