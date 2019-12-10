#include "SceneTerrainManager.h"
#include "..\Terrain\TerrainObject.h"
#include "TerrainManager.h"
#include "..\Dynasty.h"

void SceneTerrainManager::SetCurrentTerrain(const std::string& key)
{
	currentTerrain = TerrainManager::GetTerrain(key);
}

TerrainObject* SceneTerrainManager::GetCurrentTerrain()
{
	return currentTerrain;
}

void SceneTerrainManager::Delete()
{
	currentTerrain = NULL;
}