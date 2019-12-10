#include "KeyboardEventManager.h"

#include "..\Game Object\Inputable.h"

KeyboardEventManager::~KeyboardEventManager()
{
	for (KeyMgrMap::iterator it = skeMgrMap.begin(); it != skeMgrMap.end(); it++)
	{
		delete it->second;
	}

	skeMgrMap.clear();
}

void KeyboardEventManager::ProcessElements()
{
	for (KeyMgrMap::iterator it = skeMgrMap.begin(); it != skeMgrMap.end(); it++)
	{
		it->second->ProcessElements();
	}
}

void KeyboardEventManager::Register(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	KeyMgrMap::iterator it = skeMgrMap.find(k);

	if (it == skeMgrMap.end())
	{
		skeMgrMap[k] = new SingleKeyEventManager(k);
	}
	skeMgrMap[k]->Register(in, e);
}

void KeyboardEventManager::Deregister(Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e)
{
	KeyMgrMap::iterator it = skeMgrMap.find(k);

	if (it != skeMgrMap.end())
	{
		skeMgrMap[k]->Deregister(in, e);
	}
}

void KeyboardEventManager::Delete()
{
	for (KeyMgrMap::iterator it = skeMgrMap.begin(); it != skeMgrMap.end(); it++)
	{
		delete it->second;
	}

	skeMgrMap.clear();
}