#include "SingleKeyEventManager.h"

#include "..\Game Object\Inputable.h"

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY k)
{
	monitorKey = k;
}

SingleKeyEventManager::~SingleKeyEventManager()
{
	pressedInputs.clear();
	releasedInputs.clear();
}

void SingleKeyEventManager::ProcessElements()
{
	currentState = Keyboard::GetKeyState(monitorKey);

	if (previousState == false && currentState == true)
	{
		for (std::set<Inputable*>::iterator it = pressedInputs.begin(); it != pressedInputs.end(); it++)
		{
			(*it)->KeyPressed(monitorKey);
		}
	}
	else if (previousState == true && currentState == false)
	{
		for (std::set<Inputable*>::iterator it = releasedInputs.begin(); it != releasedInputs.end(); it++)
		{
			(*it)->KeyReleased(monitorKey);
		}
	}

	previousState = currentState;
}

void SingleKeyEventManager::Register(Inputable* in, INPUT_EVENT_TYPE e)
{
	if (e == KEY_PRESS)
	{
		pressedInputs.insert(in);
	}
	else
	{
		releasedInputs.insert(in);
	}
}

void SingleKeyEventManager::Deregister(Inputable* in, INPUT_EVENT_TYPE e)
{
	if (e == KEY_PRESS)
	{
		pressedInputs.erase(in);
	}
	else
	{
		releasedInputs.erase(in);
	}
}