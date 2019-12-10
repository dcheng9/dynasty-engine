#ifndef _TerrainManager
#define _TerrainManager

#include <string>
#include <map>
#include "AzulCore.h"
#include "..\Terrain\TerrainObject.h"

///
///	\ingroup AssetManagerGroup
///
class TerrainManager
{
private:
	~TerrainManager();
	static TerrainManager* singleInst;

	TerrainManager() { dPath = "HeightMaps/"; };		// Private constructor
	TerrainManager(const TerrainManager&){ };	// Prevent copy-construction
	TerrainManager& operator=(const TerrainManager&){ };	// Prevent assignment

	static TerrainManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new TerrainManager();
		return *singleInst;
	};

	std::string dPath;

	typedef std::string MapKey;
	typedef std::map<MapKey, TerrainObject*> StorageMap;
	StorageMap storage;

	void pLoadTerrain(const MapKey& key, char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV);
	TerrainObject* pGetTerrain(const MapKey& key);

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Called before runtime to load Terrains that will be used in the game
	///
	/// \param key The name you want the TerrainObject to be referred to
	///	\param heightmapFile The desired TerrainObject's HeightMap filename
	/// \param SideLength The scale of the TerrainObject
	///	\param maxheight The maximum height that will be calculated from the HeightMap
	/// \param zeroHeight The lowest height that will be calculated from the HeightMap, leave at 0
	///	\param TextureKey The name of the Texture you want the TerrainObject to have
	/// \param RepeatU Sets how you want the Texture to repeat
	/// \param RepeatV Sets how you want the Texture to repeat
	/// 
	static void LoadTerrain(const MapKey& key, char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV);
	///
	/// \brief Returns a desired TerrainObject
	///
	/// \param key The name of the TerrainObject you want to access
	/// 
	static TerrainObject* GetTerrain(const MapKey& key);

};
#endif _TerrainManager