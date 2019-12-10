#include "TerrainObject.h"
#include <assert.h>
#include <string>
#include <vector>
#include <assert.h>

#include "GpuVertTypes.h"		// Definitions for Vertices and Triangles
#include "AzulFileHdr.h"		// Azul file headers
#include "File.h"				
#include "TextureTGA.h"			// TGA parser

#include "AzulCore.h"
#include "..\Managers\ModelManager.h"
#include "..\Managers\ShaderManager.h"
#include "..\Managers\TextureManager.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Collider\Visualizer.h"
#include "..\Collider\AABB.h"
#include "..\Other Classes\MathTools.h"
#include "CellIterator.h"

#include "..\Game Object\Collidable.h"

TerrainObject::TerrainObject(const char* heightmapFile, float Sidelength, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV)
{
	// Create the model 
	// *** and save it to an .azul file ***
	// *** and loads in the the Model Manager ***
	CreateTerrainModel( heightmapFile, RepeatU, RepeatV);

	// Load back terrain model (because that's the only way for now...)
	pGObjFT = new GraphicsObject_TextureFlat(ModelManager::GetModel("AzulTerrain"), ShaderManager::GetShader("shaderFlat"), TextureManager::GetTexture(TextureKey));

	Vect tempColor = Vect(0, 0, 0, 0);

	// For debug this week only
	pGObjFT2 = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("AzulTerrain"), ShaderManager::GetShader("shaderConstColor"), tempColor); TextureKey;

	// Scale and adjust position if needed
	scale = Matrix(SCALE, Sidelength, maxheight - zeroHeight, Sidelength);

	pGObjFT->SetWorld(scale);
	pGObjFT2->SetWorld(scale);

	for (int i = 0; i < totalCells; i++)
	{
		cellsData[i].SetMinCorner(cellsData[i].GetMinCorner() * scale);
		cellsData[i].SetMaxCorner(cellsData[i].GetMaxCorner() * scale);
	}
}

TerrainObject::~TerrainObject()
{
	delete[] cellsData;

	delete pGObjFT;
	delete pGObjFT2;
}

void TerrainObject::CreateTerrainModel(const char* heightmapFile, int RepeatU, int RepeatV)
{
	// Using GLTools to read in the file
	int imgWidth, imgHeight, icomp;
	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0); // We need square images for heightmaps

	rowSize = imgWidth - 1;
	totalCells = rowSize * rowSize;
	cellWidth = 1.0f / rowSize;
	baseDefault = -(0.5f * cellWidth + (((imgWidth / 2.0f) - 1) * cellWidth));
	pixelWidth = imgWidth;

	cellsData = new TerrainCell[totalCells];

	int numVerts = (int)pow(imgWidth, 2);
	VertexStride_VUN* verts = new VertexStride_VUN[numVerts];

	int index = 0;

	for (int x = 0; x < pixelWidth; x++)
	{
		for (int y = 0; y < pixelWidth; y++)
		{
			verts[index].x = ((y * cellWidth) + baseDefault);
			verts[index].y = (float)static_cast<unsigned char>(imgData[GetPixelIndex(x, y)]) / 255.0f;
			verts[index].z = (x * cellWidth) + baseDefault;

			verts[index].u = (float)RepeatU - ((float)y / ((float)pixelWidth - 1)) * (float)RepeatU;
			verts[index].v = (float)RepeatV + (((float)x / ((float)pixelWidth - 1)) * (float)RepeatV);

			verts[index].txt = 0;

			index++;
		}
	}
	index = 0;

	int numTris = (int)pow(imgWidth - 1, 2) * 2;
	TriangleIndex* tris = new TriangleIndex[numTris];
	float temp;

	int cellsIndex = 0;

	for (int x = 0; x < rowSize; x++)
	{
		for (int y = 0; y < rowSize; y++)
		{
			tris[index] = TriangleIndex();
			tris[index].v0 = GetVertIndex(x, y);
			tris[index].v1 = GetVertIndex(x, y + 1);
			tris[index].v2 = GetVertIndex(x + 1, y);

			index++;

			tris[index] = TriangleIndex();
			tris[index].v0 = GetVertIndex(x + 1, y);
			tris[index].v1 = GetVertIndex(x, y + 1);
			tris[index].v2 = GetVertIndex(x + 1, y + 1);

			index++;

			temp = verts[GetVertIndex(y, x)].y;
			temp = min(temp, verts[GetVertIndex(y + 1, x)].y);
			temp = min(temp, verts[GetVertIndex(y + 1, x + 1)].y);
			temp = min(temp, verts[GetVertIndex(y, x + 1)].y);

			Vect tempPoint = Vect(verts[GetVertIndex(y, x)].x, temp, verts[GetVertIndex(y, x)].z);
			cellsData[cellsIndex].SetMinCorner(tempPoint);

			temp = verts[GetVertIndex(y, x)].y;
			temp = max(temp, verts[GetVertIndex(y + 1, x)].y);
			temp = max(temp, verts[GetVertIndex(y + 1, x + 1)].y);
			temp = max(temp, verts[GetVertIndex(y, x + 1)].y);

			tempPoint = Vect(verts[GetVertIndex(y + 1, x + 1)].x, temp, verts[GetVertIndex(y + 1, x + 1)].z);
			cellsData[cellsIndex].SetMaxCorner(tempPoint);

			cellsData[cellsIndex].SetXIndex(x);
			cellsData[cellsIndex].SetYIndex(y);

			cellsIndex++;
		}
	}

	SaveTerrainModel(verts, numVerts, tris, numTris);
	ModelManager::LoadModel("AzulTerrain", "AZULTERRAIN.azul");

	delete verts;
	delete tris;
}

// Saved the model data according to the .azul file format
// <nothing to change here EXCEPT the proper folder in which to save the terrain files>
void TerrainObject::SaveTerrainModel( VertexStride_VUN* pVerts, int num_verts, TriangleIndex* tlist, int num_tri)
{

	char* TerrainName = "AZULTERRAIN";									
	char* TerrainFilename = "../Assets/Models/AZULTERRAIN.azul";	// Needs to be modified to fit your specific folder within 'Assets'

	//// Write the data to a file ----------------------------
	FileHandle fh;
	FileError  ferror;
	std::vector<std::string> FBX_textNames; // (Ed) purposefully empty to be consistent 

	// 1) Create a blank header

		// // write the data
		AzulFileHdr  azulFileHdr;
		strcpy_s(azulFileHdr.objName, OBJECT_NAME_SIZE, TerrainName);

	// 2)  Write the data (Header, Buffers) to the files

	// write the header (Take 1) 

		// create the file, write the header
		ferror = File::open(fh, TerrainFilename, FILE_READ_WRITE );
		assert( ferror == FILE_SUCCESS );

		// write the data
		ferror = File::write( fh, &azulFileHdr, sizeof(azulFileHdr) );
		assert( ferror == FILE_SUCCESS );

	// update the header: numTextures, textureNamesOffset
		azulFileHdr.numTextures = FBX_textNames.size();

		// update the offset
		ferror = File::tell( fh, azulFileHdr.textureNamesOffset );
		assert( ferror == FILE_SUCCESS );

	
	std::vector<std::string>::iterator FBX_textNames_iterator;

	int i=0;
	for( FBX_textNames_iterator = FBX_textNames.begin(); 
		    FBX_textNames_iterator != FBX_textNames.end();
		    FBX_textNames_iterator++ )
	{
		const char *ss = (*FBX_textNames_iterator).c_str();
		// write the vertex data
		ferror = File::write( fh, ss, strlen(ss) + 1);
		assert( ferror == FILE_SUCCESS );
		i++;
	}

	// update the header: numVerts, VertBufferOffset

		// update the number of verts
		azulFileHdr.numVerts = num_verts;
   
		// update the offset
		ferror = File::tell( fh, azulFileHdr.vertBufferOffset );
		assert( ferror == FILE_SUCCESS );

	// write the vertex data
	ferror = File::write( fh, pVerts, num_verts * sizeof(VertexStride_VUN) );
	assert( ferror == FILE_SUCCESS );

	// update the header: numTriList, triListBufferOffset

		// update the number of verts
		azulFileHdr.numTriangles = num_tri;

		// update the offset
		ferror = File::tell( fh, azulFileHdr.triangleListBufferOffset );
		assert( ferror == FILE_SUCCESS );

	// write the triListBuffer data
	ferror = File::write( fh, tlist, num_tri * sizeof(TriangleIndex) );
	assert( ferror == FILE_SUCCESS );
	    
	// write the header (Take 2) now with updated data

		azulFileHdr.textureNamesInBytes = azulFileHdr.vertBufferOffset - azulFileHdr.textureNamesOffset;

		// reset to the beginning of file
		ferror = File::seek( fh, FILE_SEEK_BEGIN, 0 );
		assert( ferror == FILE_SUCCESS );

		// write the buffer
		ferror = File::write( fh, &azulFileHdr, sizeof(azulFileHdr) );
		assert( ferror == FILE_SUCCESS );

	// All done - bye bye
	ferror = File::close( fh );
	assert( ferror == FILE_SUCCESS );
}

void TerrainObject::Draw()
{
	pGObjFT->Render(SceneManager::GetCurrentCamera());
	pGObjFT2->Render(SceneManager::GetCurrentCamera());

	// Draws all TerrainCells
	//for (int i = 0; i < numOfCells; i++)
	//{
		//Visualizer::RenderTerrainAABB(cellsData[i]);
	//}
}

void TerrainObject::pComputeGroupAABB(const BoundingSphere* cv)
{
	Vect minVertex = cv->GetCenter();
	Vect maxVertex = cv->GetCenter();

	Vect tempMin = Vect(minVertex.X() - cv->GetRadius(), minVertex.Y() - cv->GetRadius(), minVertex.Z() - cv->GetRadius());
	Vect tempMax = Vect(maxVertex.X() + cv->GetRadius(), maxVertex.Y() + cv->GetRadius(), maxVertex.Z() + cv->GetRadius());

	minVertex.X() = min(tempMin.X(), minVertex.X());
	maxVertex.X() = max(tempMax.X(), maxVertex.X());
	minVertex.Z() = min(tempMin.Z(), minVertex.Z());
	maxVertex.Z() = max(tempMax.Z(), maxVertex.Z());

	minVertex *= scale.getInv();
	maxVertex *= scale.getInv();

	highlightedArea.SetMinCorner(minVertex);
	highlightedArea.SetMaxCorner(maxVertex);
}

int TerrainObject::GetRow(const Vect& v)
{
	int row = (int)((v.Z() / cellWidth) - (baseDefault / cellWidth));
	row = (int)MathTools::ClampAABB((float)row, 0.0f, (float)(rowSize - 1));

	return row;
}

int TerrainObject::GetCol(const Vect& v)
{
	int col = (int)((v.X() / cellWidth) - (baseDefault / cellWidth));
	col = (int)MathTools::ClampAABB((float)col, 0.0f, (float)(rowSize - 1));

	return col;
}

void TerrainObject::ComputeGroupAABB(const BoundingSphere* cv)
{
	pComputeGroupAABB(cv);
}

void TerrainObject::HighlightCell(const Vect& p)
{
	Vect tempV = p * scale.getInv();

	int index = GetCellDataIndex(GetRow(tempV), GetCol(tempV));

	Visualizer::RenderTerrainAABB(cellsData[index]);
}

void TerrainObject::HighlightCellArea(const BoundingSphere* cv)
{
	ComputeGroupAABB(cv);

	for (int i = GetRow(highlightedArea.GetMinCorner()); i <= GetRow(highlightedArea.GetMaxCorner()); i++)
	{
		for (int j = GetCol(highlightedArea.GetMinCorner()); j <= GetCol(highlightedArea.GetMaxCorner()); j++)
		{
			int index = GetCellDataIndex(i, j);

			Visualizer::RenderTerrainAABB(cellsData[index]);
		}
	}
}

CellIterator TerrainObject::SetCellIterator(TerrainCell& area)
{
	int minRow = GetRow(area.GetMinCorner());
	int maxRow = GetRow(area.GetMaxCorner());
	int minCol = GetCol(area.GetMinCorner());
	int maxCol = GetCol(area.GetMaxCorner());

	CellIterator tempIt(cellsData + GetCellDataIndex(minRow, minCol), cellsData + GetCellDataIndex(maxRow, maxCol), (maxCol - minCol), rowSize);
	cellIt = tempIt;

	return cellIt;
}

Scene* TerrainObject::GetGOScene()
{
	return NULL;
}