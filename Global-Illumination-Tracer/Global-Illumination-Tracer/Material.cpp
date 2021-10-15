#include "Material.h"

Material::Material() {
	//Default reflectance of 0.5
	reflectance = 0.5;
}

Material::Material(float inReflectance) { 
	setReflectance(inReflectance);
}

void Material::setReflectance(float inReflectance) {
	if(inReflectance >= 1) {
		reflectance = 1;
	}
	else if(inReflectance <= 0) {
		reflectance = 0;
	}
	else {
		reflectance = inReflectance;
	}
}