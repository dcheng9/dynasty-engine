#include "CommandSceneChange.h"
#include "..\Managers\SceneManager.h"

CommandSceneChange::CommandSceneChange(Scene* nextScene) : ptrSc(nextScene)
{

}

void CommandSceneChange::execute()
{
	SceneManager::EndCurrentScene();
	SceneManager::DeleteCurrentScene();
	SceneManager::SetScene(ptrSc);
}