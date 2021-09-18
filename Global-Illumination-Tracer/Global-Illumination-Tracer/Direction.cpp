#include "Direction.h"

Direction::Direction() {
	direction = Vec3(0,0,0);
}


Direction::Direction(double inX, double inY, double inZ){
	direction = Vec3(inX,inY,inZ);
}

Direction::Direction(Vec3 inVec) {
	direction = inVec;
}