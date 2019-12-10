#include "SceneManager.h"
#include "CameraManager.h"
#include "SceneTerrainManager.h"
#include "..\Dynasty.h"
#include "..\Scene\CommandSceneAddObject.h"
#include "..\Scene\CommandSceneRemoveObject.h"
#include "..\Scene\CommandSceneChange.h"

#include "..\Scene\Scene.h"

SceneManager* SceneManager::singleInst = NULL;

SceneManager::~SceneManager()
{

}

void SceneManager::Delete()
{
	delete Instance().currentCamera;
	Instance().currentScene->GetCameraManager().Delete();

	Instance().currentScene->SceneEnd();
	Instance().currentScene->Delete();
	delete Instance().currentScene;

	delete singleInst;
	singleInst = NULL;
}

void SceneManager::InitializeScene()
{
	Instance().currentScene->Initialize();
}

void SceneManager::Update()
{
	Instance().currentScene->Update();
}

void SceneManager::Draw()
{
	Instance().currentScene->Draw();
}

Camera* SceneManager::GetCurrentCamera()
{
	Instance().currentScene->GetCameraManager().UpdateCamera();
	return Instance().currentScene->GetCameraManager().GetCurrentCamera();
}

TerrainObject* SceneManager::GetCurrentTerrain()
{
	return Instance().currentScene->GetTerrainManager().GetCurrentTerrain();
}

void SceneManager::EndCurrentScene()
{
	Instance().currentScene->SceneEnd();
}

void SceneManager::DeleteCurrentScene()
{
	delete Instance().currentCamera;
	Instance().currentScene->GetCameraManager().Delete();
	Instance().currentScene->Delete();
}

void SceneManager::SetScene(Scene* sc)
{
	Instance().currentScene = sc;
	Instance().currentCamera = Instance().currentScene->GetCameraManager().GetCurrentCamera();
	InitializeScene();
}

void SceneManager::AddToScene(GameObject* go)
{
	CommandSceneAddObject* ptrAddCmd = new CommandSceneAddObject(Instance().currentScene, go);
	Instance().currentScene->RegistrationBrkr.addCommand(ptrAddCmd);
}

void SceneManager::RemoveFromScene(GameObject* go)
{
	CommandSceneRemoveObject* ptrRmvCmd = new CommandSceneRemoveObject(go);
	Instance().currentScene->RegistrationBrkr.addCommand(ptrRmvCmd);
}

void SceneManager::SetNextScene(Scene* nextScene)
{
	CommandSceneChange* ptrScChg = new CommandSceneChange(nextScene);
	Instance().currentScene->RegistrationBrkr.addCommand(ptrScChg);
}