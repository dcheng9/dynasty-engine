#include "CommandSceneAddObject.h"
#include "..\Game Object\GameObject.h"

CommandSceneAddObject::CommandSceneAddObject(Scene* sc, GameObject* go) : ptrSc(sc), ptrGO(go)
{

}

void CommandSceneAddObject::execute()
{
	ptrGO->SetScene(ptrSc);
	ptrGO->SceneEntry();
}