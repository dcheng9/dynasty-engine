#include "ShaderManager.h"

ShaderManager* ShaderManager::singleInst = NULL;

ShaderManager::~ShaderManager()
{

}

void ShaderManager::pLoadShader(const MapKey& key, const std::string& path)
{
	storage[key] = new ShaderObject((dPath + path).c_str());
}

ShaderObject* ShaderManager::pGetShader(const MapKey& key)
{
	return storage[key];
}

void ShaderManager::Delete()
{
	for (std::map<MapKey, ShaderObject*>::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		delete it->second;
	}

	Instance().storage.clear();

	delete singleInst;
	singleInst = NULL;
}

void ShaderManager::LoadShader(const MapKey& key, const std::string& path)
{
	Instance().pLoadShader(key, path);
}

ShaderObject* ShaderManager::GetShader(const MapKey& key)
{
	return Instance().pGetShader(key);
}