#include "Scene.h"

Scene::Scene() {
	//--Hardcoded room.--//

	//Tak
	room[0] = Triangle(vertexList[1], vertexList[2], vertexList[0], ColorDbl(200, 200, 200));
	room[1] = Triangle(vertexList[2], vertexList[3], vertexList[0], ColorDbl(200, 200, 200));
	room[2] = Triangle(vertexList[3], vertexList[4], vertexList[0], ColorDbl(200, 200, 200));
	room[3] = Triangle(vertexList[4], vertexList[5], vertexList[0], ColorDbl(200, 200, 200));
	room[4] = Triangle(vertexList[5], vertexList[6], vertexList[0], ColorDbl(200, 200, 200));
	room[5] = Triangle(vertexList[6], vertexList[1], vertexList[0], ColorDbl(200, 200, 200));

	//Golv
	room[6] = Triangle(vertexList[8], vertexList[7], vertexList[9], ColorDbl(200, 200, 200));
	room[7] = Triangle(vertexList[9], vertexList[7], vertexList[10], ColorDbl(200, 200, 200));
	room[8] = Triangle(vertexList[10], vertexList[7], vertexList[11], ColorDbl(200, 200, 200));
	room[9] = Triangle(vertexList[11], vertexList[7], vertexList[12], ColorDbl(200, 200, 200));
	room[10] = Triangle(vertexList[12], vertexList[7], vertexList[13], ColorDbl(200, 200, 200));
	room[11] = Triangle(vertexList[13], vertexList[7], vertexList[8], ColorDbl(200, 200, 200));

	//Vägg 1
	room[12] = Triangle(vertexList[1], vertexList[8], vertexList[9], ColorDbl(255, 0, 0));
	room[13] = Triangle(vertexList[1], vertexList[9], vertexList[2], ColorDbl(255, 0, 0));

	//Vägg 2
	room[14] = Triangle(vertexList[2], vertexList[9], vertexList[10], ColorDbl(0, 255, 0));
	room[15] = Triangle(vertexList[2], vertexList[10], vertexList[3], ColorDbl(0, 255, 0));

	//Vägg 3
	room[16] = Triangle(vertexList[3], vertexList[10], vertexList[11], ColorDbl(0, 0, 255));
	room[17] = Triangle(vertexList[3], vertexList[11], vertexList[4], ColorDbl(0, 0, 255));

	//Vägg 4
	room[18] = Triangle(vertexList[4], vertexList[11], vertexList[12], ColorDbl(255, 255, 0));
	room[19] = Triangle(vertexList[4], vertexList[12], vertexList[5], ColorDbl(255, 255, 0));
	
	//Vägg 5
	room[20] = Triangle(vertexList[5], vertexList[12], vertexList[13], ColorDbl(0, 255, 255));
	room[21] = Triangle(vertexList[5], vertexList[13], vertexList[6], ColorDbl(0, 255, 255));
	
	//Vägg 6
	room[22] = Triangle(vertexList[6], vertexList[13], vertexList[8], ColorDbl(255, 0, 255));
	room[23] = Triangle(vertexList[6], vertexList[8], vertexList[1], ColorDbl(255, 0, 255));


}
