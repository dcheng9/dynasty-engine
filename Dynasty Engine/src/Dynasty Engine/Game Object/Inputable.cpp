#include "Inputable.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\Scene.h"

void Inputable::KeyEventRegistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	GetGOScene()->RegisterKeyEvent(this, k, e);
}

void Inputable::KeyEventDeregistration(AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	GetGOScene()->DeregisterKeyEvent(this, k, e);
}