#ifndef _ShaderManager
#define _ShaderManager

#include <string>
#include <map>
#include "AzulCore.h"
#include "ShaderObject.h"

///
///	\ingroup AssetManagerGroup
///
class ShaderManager
{
private:
	~ShaderManager();
	static ShaderManager* singleInst;

	ShaderManager() { dPath = "Shaders/"; };		// Private constructor
	ShaderManager(const ShaderManager&){ };	// Prevent copy-construction
	ShaderManager& operator=(const ShaderManager&){ };	// Prevent assignment

	static ShaderManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new ShaderManager();
		return *singleInst;
	};

	std::string dPath;

	typedef std::string MapKey;
	typedef std::map<MapKey, ShaderObject*> StorageMap;
	StorageMap storage;

	void pLoadShader(const MapKey& key, const std::string& path);
	ShaderObject* pGetShader(const MapKey& key);

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Called before runtime to load Shaders that will be used in the game
	///
	/// \param key The name you want the Shader to be referred to 
	///	\param path The desired Shader's filename
	/// 
	static void LoadShader(const MapKey& key, const std::string& path);
	///
	/// \brief Returns a desired Shader
	///
	/// \param key The name of the Shader you want to access
	/// 
	static ShaderObject* GetShader(const MapKey& key);;

};
#endif _ShaderManager