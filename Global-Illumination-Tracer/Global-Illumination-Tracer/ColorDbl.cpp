#include "ColorDbl.h"
ColorDbl::ColorDbl() {
	values = glm::vec3(0, 0, 0);
}
ColorDbl::ColorDbl(double inR, double inG, double inB){
	values = glm::vec3(inR, inG, inB);
}

ColorDbl::ColorDbl(glm::vec3 inVec) {
	values = inVec;
}

glm::vec3 ColorDbl::GetValues()
{
	return values;
}
