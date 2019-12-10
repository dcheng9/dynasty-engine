#include "Updatable.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\Scene.h"

void Updatable::UpdateRegistration()
{
	GetGOScene()->RegisterUpdate(this);
}

void Updatable::UpdateDeregistration()
{
	GetGOScene()->DeregisterUpdate(this);
}