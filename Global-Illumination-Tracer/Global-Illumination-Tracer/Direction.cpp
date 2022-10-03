#include "Direction.h"

Direction::Direction() {
	direction = glm::vec3(0,0,0);
}


Direction::Direction(double inX, double inY, double inZ){
	direction = glm::vec3(inX,inY,inZ);
}

Direction::Direction(glm::vec3 inVec) {
	direction = inVec;
}