#include "TextureManager.h"

TextureManager* TextureManager::singleInst = NULL;

TextureManager::~TextureManager()
{

}

void TextureManager::pLoadTexture(const MapKey& key, const std::string& path)
{
	storage[key] = new Texture((dPath + path).c_str());
}

Texture* TextureManager::pGetTexture(const MapKey& key)
{
	return storage[key];
}

void TextureManager::Delete()
{
	for (std::map<MapKey, Texture*>::iterator it = Instance().storage.begin(); it != Instance().storage.end(); it++)
	{
		delete it->second;
	}

	Instance().storage.clear();

	delete singleInst;
	singleInst = NULL;
}

void TextureManager::LoadTexture(const MapKey& key, const std::string& path)
{
	Instance().pLoadTexture(key, path);
}

Texture* TextureManager::GetTexture(const MapKey& key)
{
	return Instance().pGetTexture(key);
}