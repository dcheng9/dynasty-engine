#ifndef _TextureManager
#define _TextureManager

#include <string>
#include <map>
#include "AzulCore.h"
#include "Texture.h"

///
///	\ingroup AssetManagerGroup
///
class TextureManager
{
private:
	~TextureManager();
	static TextureManager* singleInst;

	TextureManager() { dPath = "Textures/"; };		// Private constructor
	TextureManager(const TextureManager&){ };	// Prevent copy-construction
	TextureManager& operator=(const TextureManager&){ };	// Prevent assignment

	static TextureManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new TextureManager();
		return *singleInst;
	};

	std::string dPath;

	typedef std::string MapKey;
	typedef std::map<MapKey, Texture*> StorageMap;
	StorageMap storage;

	void pLoadTexture(const MapKey& key, const std::string& path);
	Texture* pGetTexture(const MapKey& key);

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Called before runtime to load Textures that will be used in the game
	///
	/// \param key The name you want the Texture to be referred to
	///	\param path The desired Texture's filename
	/// 
	static void LoadTexture(const MapKey& key, const std::string& path);
	///
	/// \brief Returns a desired Texture
	///
	/// \param key The name of the Texture you want to access
	/// 
	static Texture* GetTexture(const MapKey& key);

};
#endif _TextureManager