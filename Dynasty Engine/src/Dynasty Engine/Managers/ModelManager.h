#ifndef _ModelManager
#define _ModelManager

#include <string>
#include <map>
#include "AzulCore.h"
#include "Model.h"

///
///	\ingroup AssetManagerGroup
///
class ModelManager
{
private:
	~ModelManager();
	static ModelManager* singleInst;

	ModelManager() { dPath = "Models/"; };		// Private constructor
	ModelManager(const ModelManager&){ };	// Prevent copy-construction
	ModelManager& operator=(const ModelManager&){ };	// Prevent assignment

	static ModelManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new ModelManager();
		return *singleInst;
	};

	std::string dPath;

	typedef std::string MapKey;
	typedef std::map<MapKey, Model*> StorageMap;
	StorageMap storage;

	void pLoadModel(const MapKey& key, const std::string& path);
	Model* pGetModel(const MapKey& key);

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Called before runtime to load Models that will be used in the game
	///
	/// \param key The name you want the Model to be referred to
	///	\param path The desired Model's filename
	/// 
	static void LoadModel(const MapKey& key, const std::string& path);
	///
	/// \brief Returns a desired Model
	///
	/// \param key The name of the Model you want to access
	/// 
	static Model* GetModel(const MapKey& key);

};
#endif _ModelManager