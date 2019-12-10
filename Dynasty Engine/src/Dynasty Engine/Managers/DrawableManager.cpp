#include "DrawableManager.h"

#include "..\Game Object\Drawable.h"

DrawableManager::~DrawableManager()
{
	storage.clear();
}

void DrawableManager::ProcessElements()
{
	for (StorageSet::iterator it = storage.begin(); it != storage.end(); it++)
	{
		(*it)->Draw();
	}
}

void DrawableManager::Register(Drawable* dr)
{
	storage.insert(dr);
}

void DrawableManager::Deregister(Drawable* dr)
{
	storage.erase(dr);
}

void DrawableManager::Delete()
{
	storage.clear();
}