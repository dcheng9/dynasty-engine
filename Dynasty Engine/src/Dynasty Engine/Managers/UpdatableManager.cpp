#include "UpdatableManager.h"
#include "..\Game Object\Updatable.h"

UpdatableManager::~UpdatableManager()
{
	storage.clear();
}

void UpdatableManager::ProcessElements()
{
	for (StorageSet::iterator it = storage.begin(); it != storage.end(); it++)
	{
		(*it)->Update();
	}
}

void UpdatableManager::Register(Updatable* up)
{
	storage.insert(up);
}

void UpdatableManager::Deregister(Updatable* up)
{
	storage.erase(up);
}

void UpdatableManager::Delete()
{
	storage.clear();
}