#include "..\Dynasty Engine\Dynasty.h"
#include "..\Dynasty Engine\Managers\ModelManager.h"
#include "..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\Dynasty Engine\Managers\TextureManager.h"
#include "..\Dynasty Engine\Managers\TerrainManager.h"

#include "..\Dynasty Engine\Managers\SceneManager.h"

#include "Scenes\IntroScene.h"

void Dynasty::LoadResources()
{
	//---------------------------------------------------------------------------------------------------------
	// Load the Models
	//---------------------------------------------------------------------------------------------------------

	ModelManager::LoadModel("modelBoundingSphere", "BoundingSphere.azul");
	ModelManager::LoadModel("modelBoundingBox", "BoundingBox.azul");
	ModelManager::LoadModel("modelSpaceFrigate", "space_frigate.azul");
	ModelManager::LoadModel("modelCottage", "Cottage.azul");

	//---------------------------------------------------------------------------------------------------------
	// Load the Textures
	//---------------------------------------------------------------------------------------------------------

	TextureManager::LoadTexture("textSpaceFrigate", "space_frigate.tga");
	TextureManager::LoadTexture("textGrid", "grid.tga");

	for (int i = 0; i<ModelManager::GetModel("modelCottage")->numTextures; i++)
	{
		TextureManager::LoadTexture("textCottage" + std::to_string(i), ModelManager::GetModel("modelCottage")->getTextureName(i));
	}

	//---------------------------------------------------------------------------------------------------------
	// Load the Shaders
	//---------------------------------------------------------------------------------------------------------

	ShaderManager::LoadShader("shaderFlat", "textureFlatRender");
	ShaderManager::LoadShader("shaderConstColor", "colorConstantRender");

	//---------------------------------------------------------------------------------------------------------
	// Load the Terrains
	//---------------------------------------------------------------------------------------------------------

	TerrainManager::LoadTerrain("terrainLevel0", "testHeightMap.tga", 500, 30, 0, "textGrid", 1, 1);
	TerrainManager::LoadTerrain("terrainLevel1", "testComplexHeightMap.tga", 500, 40, 0, "textGrid", 1, 1);

	SceneManager::SetScene(new IntroScene);
}