#include "SceneTest.h"

#include "..\..\Dynasty Engine\Game Object\GameObject.h"

#include "..\Objects\Spaceship.h"
#include "..\Objects\Box.h"
#include "..\Objects\Cottage.h"
#include "..\Other\BulletFactory.h"
#include "..\Other\GodCamera.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"

#include "..\..\Dynasty Engine\Collider\Visualizer.h"

void SceneTest::Initialize()
{
	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(-50.0f, 200.0f, 0.0f);
	Vect lookAt3DCam(-40.0f, -20.0f, 0.0f);
	GetCameraManager().GetCurrentCamera()->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	GetCameraManager().GetCurrentCamera()->updateCamera();

	SetTerrain("terrainLevel1");

	Vect shipPos1 = Vect(0, 35, -100);
	testSpaceship = new Spaceship(shipPos1);
	Vect shipPos2 = Vect(0, 35, -150);
	testSpaceship2 = new Spaceship(shipPos2);
	Vect shipPos3 = Vect(-100, 35, -125);
	testSpaceship3 = new Spaceship(shipPos3);

	testBox = new Box();

	Vect cottagePos1 = Vect(-50, 20, 0);
	testCottage1 = new Cottage(cottagePos1);
	Vect cottagePos2 = Vect(50, 20, 0);
	testCottage2 = new Cottage(cottagePos2);
	Vect cottagePos3 = Vect(0, 20, 50);
	testCottage3 = new Cottage(cottagePos3);
	Vect cottagePos4 = Vect(90, 20, 0);
	testCottage4 = new Cottage(cottagePos4);

	godCam = new GodCamera();

	AddToScene(testSpaceship);
	//AddToScene(testSpaceship2);
	///AddToScene(testSpaceship3);

	AddToScene(testBox);

	AddToScene(testCottage1);
	AddToScene(testCottage2);
	AddToScene(testCottage3);
	AddToScene(testCottage4);

	AddToScene(godCam);

	SetCollisionPair<Spaceship, Cottage>();
	SetCollisionSelf<Spaceship>();
	SetCollisionSelf<Cottage>();
	SetCollisionTerrain<Spaceship>();
}

void SceneTest::SceneEnd()
{
	delete testBox;
	delete testCottage1;
	delete testCottage2;
	delete testCottage3;
	delete testCottage4;
	delete testSpaceship;
	delete testSpaceship2;
	delete testSpaceship3;
	delete godCam;
}