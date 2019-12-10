#include "IntroScene.h"

#include "..\..\Dynasty Engine\Game Object\GameObject.h"

#include "..\Objects\Box.h"
#include "..\Other\GodCamera.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"

void IntroScene::Initialize()
{
	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(-50.0f, 1000.0f, 0.0f);
	Vect lookAt3DCam(-40.0f, -20.0f, 0.0f);
	GetCameraManager().GetCurrentCamera()->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	GetCameraManager().GetCurrentCamera()->updateCamera();

	SetTerrain("terrainLevel0");

	testBox = new Box();

	godCam = new GodCamera();

	AddToScene(testBox);
	AddToScene(godCam);
}

void IntroScene::SceneEnd()
{
	delete testBox;
	delete godCam;
}