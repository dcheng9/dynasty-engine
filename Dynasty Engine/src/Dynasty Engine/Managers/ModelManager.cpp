#include "ModelManager.h"

ModelManager* ModelManager::singleInst = NULL;

ModelManager::~ModelManager()
{

}

void ModelManager::pLoadModel(const MapKey& key, const std::string& path)
{
	storage[key] = new Model((dPath + path).c_str());
}

Model* ModelManager::pGetModel(const MapKey& key)
{
	return storage[key];
}

void ModelManager::Delete()
{
	for (std::map<MapKey, Model*>::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		delete it->second;
	}
	
	Instance().storage.clear();

	delete singleInst;
	singleInst = NULL;
}

void ModelManager::LoadModel(const MapKey& key, const std::string& path)
{
	Instance().pLoadModel(key, path);
}

Model* ModelManager::GetModel(const MapKey& key)
{
	return Instance().pGetModel(key);
}