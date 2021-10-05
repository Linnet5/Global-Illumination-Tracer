#include "Camera.h"

int x = 0;
int y = 0;
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
	dis3 = std::uniform_real_distribution<float>(0, 3);

	for (int i = 0; i < 800; i++) {
		for (int j = 0; j < 800; j++) {
			glm::vec3 pixelPosition = glm::vec3(0, -1 + 0.0025 * i, 1 - 0.0025 * j);
			Ray renderRay = Ray(eye1, dummy, ColorDbl(glm::vec3(0, 0, 0)));

			pixels[i, j]->setColor(renderEquation(eye1, pixelPosition - eye1, renderRay));

			/*
			glm::vec3 tempColor = glm::vec3(0, 0, 0);
			for (int a = 0; a < 5; a++) {
				tempColor += renderEquation(eye1, pixelPosition - eye1, renderRay);
			}
			tempColor = tempColor / 5.0f;
			pixels[i, j]->setColor(tempColor);
			*/


			/* TEMPOR�RT UTKOMMENTERAD
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
	
	if (renderRay.endPointTriangle != nullptr) {
		glm::vec3 albedo = renderRay.endPointTriangle->color.GetValues() * renderRay.endPointTriangle->reflectance;
		albedo = glm::normalize(albedo);

		const int nSamples = 1;
		for (int i = 0; i < nSamples; i++) {
			float rand1 = dis(gen);
			float rand2 = dis(gen);
			float rand3 = dis(gen);

			float theta = (pi * rand1) / 3;
			float azimuth = 2 * pi * rand2;
			//std::cout << theta << " " << azimuth <<std::endl;


			//all disepation coditions
			if (!lightSourceTouched && (1 - renderRay.endPointTriangle->reflectance) < rand3) {
				glm::vec3 normal = renderRay.endPointTriangle->calculateNormal();
				glm::vec3 outVec = normal;
				glm::vec3 offset = 0.0001f * normal; //beh�ver nog, udda nog s� blev det b�ttre resulata med - offset, r�tt s�ker att v�ran tetrahedron har en fucked normal
				/*
				outVec.x = sin(theta) * cos(azimuth);
				outVec.y = sin(theta) * sin(azimuth);
				outVec.z = cos(theta); //FEL alla punkter p� taket syns inte : bevis cos(0 : pi/2) >= 0; s� rayn stusar altid upp�t : igenom taket,
				outVec = glm::normalize(outVec);
				*/
				glm::vec3 temp = normal + glm::vec3(1, 1, 1);
				glm::vec3 tangent = glm::cross(normal, temp);

				//FIX???
				if (glm::length(tangent) == 0)
					tangent = normal;

				outVec = glm::normalize(glm::rotate(outVec, theta, tangent));// kolla documentation f�r hur vi g�r detta https://glm.g-truc.net/0.9.3/api/a00199.html
				outVec = glm::normalize((glm::rotate(outVec, azimuth, normal)));

				/*
				if (glm::dot(normal, outVec) < 0) {
					outVec = outVec * -1.0f;
					//std::cout << "HUR" << x << std::endl;
				}//kanske beh�ver s� rays inte fastnar i object
				*/
				glm::vec3 bdrf = (pi * albedo * cos(theta) * sin(theta)) / ((renderRay.endPointTriangle->reflectance) * nSamples);

				radiance = renderEquation(renderRay.end, outVec, renderRay);
				glm::vec3 newRadiance = radiance * bdrf + directRadiance(renderRay, albedo); //kanske problem att den klagar p� radiance inte har v�rde f�r alla decs av readiance �r i if satser.

				return newRadiance;
			}
			else if (lightSourceTouched) {
				return glm::vec3(1.0, 1.0, 1.0); //eller vad L0 �r
			}
			else {
				return glm::vec3(0.0, 0.0, 0.0);
			}
		}
	}
	else {
		;
		std::cout << y << std::endl;
		y++;
	}
	return glm::vec3(0, 0, 0);
	
}

glm::vec3 Camera::directRadiance(Ray renderRay, glm::vec3 albedo)
{
	glm::vec3 e1 = glm::normalize(glm::vec3(3.5f, 5.5f, 5.0f) - glm::vec3(3.5f, 2.5f, 5.0f));
	glm::vec3 e2 = glm::normalize(glm::vec3(6.5f, 2.5f, 5.0f) - glm::vec3(3.5f, 2.5f, 5.0f));
	Ray dummyRay = Ray(renderRay.end, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	glm::vec3 shadowRadiance = glm::vec3(0,0,0);
	int n_samples = 10;
	for (int i = 0; i < n_samples; i++) {
		float c1 = dis3(gen);
		float c2 = dis3(gen);
		
		bool V = true;

		glm::vec3 randCord = glm::vec3(3.5f, 2.5f, 5.0f) + c1 * e1 + c2 * e2;
		glm::vec3 shadowRay = randCord - renderRay.end;
		
		for (int obj = 0; obj < 1; obj++) {
			if (scene.objects[obj]->renderFunction(dummyRay, shadowRay)) {
				V = false;
			}
		}

		if (V) {
			shadowRadiance +=  -1 * glm::dot(randCord, glm::vec3(0, 0, -1)) * (glm::dot(randCord, glm::normalize(renderRay.endPointTriangle->calculateNormal())) / (randCord * randCord * randCord * randCord));
		}
	}
	glm::vec3 G = (albedo * 9.0f) / (pi * n_samples);
	
	return G * shadowRadiance;
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