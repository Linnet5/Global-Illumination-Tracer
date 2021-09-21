#include "ColorDbl.h"
ColorDbl::ColorDbl() {
	values = Vec3(0, 0, 0);
}
ColorDbl::ColorDbl(double inR, double inG, double inB){
	values = Vec3(inR, inG, inB);
}

ColorDbl::ColorDbl(Vec3 inVec) {
	values = inVec;
}

Vec3 ColorDbl::GetValues()
{
	return values;
}
