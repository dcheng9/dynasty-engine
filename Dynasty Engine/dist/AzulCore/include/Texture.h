#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb6.h"

#define TEXTURE_ASSET_NAME_SIZE 64

class Texture
{
public:
	Texture();
	Texture(const char * const _assetName);
	void set(const char * const _assetName,
		GLuint _TextureID,
		GLenum minFilter,
		GLenum magFilter,
		GLenum wrapMode,
		int width,
		int height);

private:
	char assetName[TEXTURE_ASSET_NAME_SIZE];

	void privLoadTexture(const char * const _assetName, GLuint *&textureID, int &width, int &height);
	bool privLoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode, int &width, int &height);


public:
	GLuint textureID;
	GLenum minFilter;
	GLenum magFilter;
	GLenum wrapMode;
	int width;
	int height;
};


#endif