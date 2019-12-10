#include "Scene.h"
#include "CommandUpdateRegistration.h"
#include "CommandUpdateDeregistration.h"
#include "CommandDrawRegistration.h"
#include "CommandDrawDeregistration.h"
#include "CommandAlarmRegistration.h"
#include "CommandAlarmDeregistration.h"
#include "CommandKeyEventRegistration.h"
#include "CommandKeyEventDeregistration.h"
#include "CommandSceneAddObject.h"
#include "CommandSceneRemoveObject.h"

#include "..\Collider\Visualizer.h"


void Scene::RegisterUpdate(Updatable* up)
{
	CommandUpdateRegistration* ptrUpCmd = new CommandUpdateRegistration(&UpdateMgr, up);
	RegistrationBrkr.addCommand(ptrUpCmd);
}

void Scene::DeregisterUpdate(Updatable* up)
{
	CommandUpdateDeregistration* ptrUpCmd = new CommandUpdateDeregistration(&UpdateMgr, up);
	RegistrationBrkr.addCommand(ptrUpCmd);
}

void Scene::Update()
{
	RegistrationBrkr.ExecuteCommands();

	AlarmMgr.ProcessElements();

	KeyEventMgr.ProcessElements();

	UpdateMgr.ProcessElements();

	CollisionMgr.ProcessCollisions();
}

void Scene::RegisterDraw(Drawable* dr)
{
	CommandDrawRegistration* ptrDrCmd = new CommandDrawRegistration(&DrawMgr, dr);
	RegistrationBrkr.addCommand(ptrDrCmd);
}

void Scene::DeregisterDraw(Drawable* dr)
{
	CommandDrawDeregistration* ptrDrCmd = new CommandDrawDeregistration(&DrawMgr, dr);
	RegistrationBrkr.addCommand(ptrDrCmd);
}

void Scene::Draw()
{
	DrawMgr.ProcessElements();
	Visualizer::ProcessElements();
}

void Scene::RegisterAlarm(AlarmMarker* am)
{
	CommandAlarmRegistration* ptrAmCmd = new CommandAlarmRegistration(&AlarmMgr, am);
	RegistrationBrkr.addCommand(ptrAmCmd);
}

void Scene::DeregisterAlarm(AlarmMarker* am)
{
	CommandAlarmDeregistration* ptrAmCmd = new CommandAlarmDeregistration(&AlarmMgr, am);
	RegistrationBrkr.addCommand(ptrAmCmd);
}

void Scene::RegisterKeyEvent(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	CommandKeyEventRegistration* ptrKeCmd = new CommandKeyEventRegistration(&KeyEventMgr, in, k, e);
	RegistrationBrkr.addCommand(ptrKeCmd);
}

void Scene::DeregisterKeyEvent(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	CommandKeyEventDeregistration* ptrKeCmd = new CommandKeyEventDeregistration(&KeyEventMgr, in, k, e);
	RegistrationBrkr.addCommand(ptrKeCmd);
}

void Scene::AddToScene(GameObject* go)
{
	CommandSceneAddObject* ptrAddCmd = new CommandSceneAddObject(this, go);
	RegistrationBrkr.addCommand(ptrAddCmd);
}

void Scene::RemoveFromScene(GameObject* go)
{
	CommandSceneRemoveObject* ptrRmvCmd = new CommandSceneRemoveObject(go);
	RegistrationBrkr.addCommand(ptrRmvCmd);
}

void Scene::SetTerrain(const std::string& key)
{
	DeregisterDraw(TerrainMgr.GetCurrentTerrain());
	TerrainMgr.SetCurrentTerrain(key);
	RegisterDraw(TerrainMgr.GetCurrentTerrain());
}

void Scene::Delete()
{
	Visualizer::ClearVisualizer();
	TerrainMgr.Delete();
	UpdateMgr.Delete();
	DrawMgr.Delete();
	AlarmMgr.Delete();
	KeyEventMgr.Delete();
	CollisionMgr.Delete();
}