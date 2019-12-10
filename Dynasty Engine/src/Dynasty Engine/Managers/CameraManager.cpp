#include "CameraManager.h"
#include "Camera.h"
#include "..\Dynasty.h"
#include "SceneManager.h"

CameraManager::~CameraManager()
{

}

CameraManager::CameraManager()
{
	currentCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	currentCamera->setViewport(0, 0, Dynasty::GetWidth(), Dynasty::GetHeight());
	currentCamera->setPerspective(35.0f, float(Dynasty::GetWidth()) / float(Dynasty::GetHeight()), 1.0f, 5000.0f);

	// Orient Camera
	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(0.0f, 0.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	currentCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	currentCamera->updateCamera();
}

void CameraManager::Delete()
{
}

void CameraManager::SetCurrentCamera(Camera* newCamera)
{
	currentCamera = newCamera;
}

void CameraManager::UpdateCamera()
{
	currentCamera->updateCamera();
}

Camera* CameraManager::GetCurrentCamera()
{
	return currentCamera;
}