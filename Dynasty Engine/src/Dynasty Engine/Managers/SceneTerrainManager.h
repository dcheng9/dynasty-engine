#ifndef _SceneTerrainManager
#define _SceneTerrainManager

#include <string>
#include "AzulCore.h"

class TerrainObject;

///
///	\ingroup OtherManagerGroup
///
class SceneTerrainManager
{
private:
	TerrainObject* currentTerrain;


public:
	virtual ~SceneTerrainManager(){};
	SceneTerrainManager(){};
	SceneTerrainManager(const SceneTerrainManager&) = delete;
	SceneTerrainManager& operator=(const SceneTerrainManager&) = delete;

	///
	/// \brief Set a new TerrainObject for the current Scene
	///
	/// \param key The new TerrainObject you want to change to
	/// 
	void SetCurrentTerrain(const std::string& key);
	///
	/// \brief Returns the current Scene's TerrainObject
	///
	TerrainObject* GetCurrentTerrain();
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();

};
#endif _SceneTerrainManager