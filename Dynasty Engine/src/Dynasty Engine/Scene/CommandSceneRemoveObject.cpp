#include "CommandSceneRemoveObject.h"

CommandSceneRemoveObject::CommandSceneRemoveObject(GameObject* go) : ptrGO(go)
{

}

void CommandSceneRemoveObject::execute()
{
	ptrGO->SceneExit();
}