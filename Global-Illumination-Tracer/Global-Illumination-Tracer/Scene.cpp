#include "Scene.h"
#include "Tetrahedron.h"
#include "Sphere.h"

Scene::Scene() {
	//--Hardcoded room.--//

	Material walls = Material(0.18);
	Material floorRoof = Material(0.18);
	Material lightMaterial = Material(0.5);

	//Tak
	room[0] = Triangle(vertexList[1], vertexList[2], vertexList[0], ColorDbl(200, 200, 200), floorRoof);
	room[1] = Triangle(vertexList[2], vertexList[3], vertexList[0], ColorDbl(200, 200, 200), floorRoof);
	room[2] = Triangle(vertexList[3], vertexList[4], vertexList[0], ColorDbl(200, 200, 200), floorRoof);
	room[3] = Triangle(vertexList[4], vertexList[5], vertexList[0], ColorDbl(200, 200, 200), floorRoof);
	room[4] = Triangle(vertexList[5], vertexList[6], vertexList[0], ColorDbl(200, 200, 200), floorRoof);
	room[5] = Triangle(vertexList[6], vertexList[1], vertexList[0], ColorDbl(200, 200, 200), floorRoof); //LightSource inuti denna triangle

	//Golv
	room[6] = Triangle(vertexList[8], vertexList[7], vertexList[9], ColorDbl(200, 200, 200), floorRoof);
	room[7] = Triangle(vertexList[9], vertexList[7], vertexList[10], ColorDbl(200, 200, 200), floorRoof);
	room[8] = Triangle(vertexList[10], vertexList[7], vertexList[11], ColorDbl(200, 200, 200), floorRoof);
	room[9] = Triangle(vertexList[11], vertexList[7], vertexList[12], ColorDbl(200, 200, 200), floorRoof);
	room[10] = Triangle(vertexList[12], vertexList[7], vertexList[13], ColorDbl(200, 200, 200), floorRoof);
	room[11] = Triangle(vertexList[13], vertexList[7], vertexList[8], ColorDbl(200, 200, 200), floorRoof);

	//V�gg 1
	room[12] = Triangle(vertexList[1], vertexList[8], vertexList[9], ColorDbl(255, 0, 0), walls);
	room[13] = Triangle(vertexList[1], vertexList[9], vertexList[2], ColorDbl(255, 0, 0), walls);

	//V�gg 2
	room[14] = Triangle(vertexList[2], vertexList[9], vertexList[10], ColorDbl(0, 255, 0), walls);
	room[15] = Triangle(vertexList[2], vertexList[10], vertexList[3], ColorDbl(0, 255, 0), walls);

	//V�gg 3
	room[16] = Triangle(vertexList[3], vertexList[10], vertexList[11], ColorDbl(0, 0, 255), walls);
	room[17] = Triangle(vertexList[3], vertexList[11], vertexList[4], ColorDbl(0, 0, 255), walls);

	//V�gg 4
	room[18] = Triangle(vertexList[4], vertexList[11], vertexList[12], ColorDbl(255, 255, 0), walls);
	room[19] = Triangle(vertexList[4], vertexList[12], vertexList[5], ColorDbl(255, 255, 0), walls);
	
	//V�gg 5
	room[20] = Triangle(vertexList[5], vertexList[12], vertexList[13], ColorDbl(0, 255, 255), walls);
	room[21] = Triangle(vertexList[5], vertexList[13], vertexList[6], ColorDbl(0, 255, 255), walls);
	
	//V�gg 6
	room[22] = Triangle(vertexList[6], vertexList[13], vertexList[8], ColorDbl(255, 0, 255), walls);
	room[23] = Triangle(vertexList[6], vertexList[8], vertexList[1], ColorDbl(255, 0, 255), walls);

	//Lightsource as an object
	lightList[0] = LightSource(lightVertex[0], lightVertex[1], lightVertex[2], lightVertex[3], 1); 

	//List of all objects in the scene
	objects[0] = new Tetrahedron();
	objects[1] = new Sphere();
}
