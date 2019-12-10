#include "GameObject.h"
#include "Camera.h"
#include "..\Scene\Scene.h"
#include "..\Managers\CameraManager.h"
#include "..\Managers\SceneManager.h"

GameObject::GameObject()
{
	currentScene = NULL;
}

void GameObject::MarkForSceneExit()
{
	if (currentScene != NULL)
	{
		currentScene->RemoveFromScene(this);
	}
}

void GameObject::SetScene(Scene* sc)
{
	currentScene = sc;
}

Scene* GameObject::GetGOScene()
{
	return currentScene;
}

Camera* GameObject::GetSceneCamera()
{
	return currentScene->GetCameraManager().GetCurrentCamera();
}