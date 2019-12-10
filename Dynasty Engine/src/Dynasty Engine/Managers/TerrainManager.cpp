#include "TerrainManager.h"

TerrainManager* TerrainManager::singleInst = NULL;

TerrainManager::~TerrainManager()
{

}

void TerrainManager::pLoadTerrain(const MapKey& key, char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV)
{
	storage[key] = new TerrainObject((dPath + heightmapFile).c_str(), Sidelength, maxheight, zeroHeight, TextureKey, RepeatU, RepeatV);
}

TerrainObject* TerrainManager::pGetTerrain(const MapKey& key)
{
	return storage[key];
}

void TerrainManager::Delete()
{
	for (std::map<MapKey, TerrainObject*>::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		delete it->second;
	}

	Instance().storage.clear();

	delete singleInst;
	singleInst = NULL;
}

void TerrainManager::LoadTerrain(const MapKey& key, char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV)
{
	Instance().pLoadTerrain(key, heightmapFile, Sidelength, maxheight, zeroHeight, TextureKey, RepeatU, RepeatV);
}

TerrainObject* TerrainManager::GetTerrain(const MapKey& key)
{
	return Instance().pGetTerrain(key);
}