#ifndef _TerrainObject
#define _TerrainObject

#include "..\Game Object\Drawable.h"
#include "Matrix.h"
#include <tuple>
#include "sb6.h"		// Provides definitions for GLByte, etc.
#include "TerrainCell.h"
#include "CellIterator.h"

class GraphicsObject_TextureFlat;
class GraphicsObject_WireframeConstantColor;

struct VertexStride_VUN;	// Model Vertex type (fwd declared)
struct TriangleIndex;		// Model Triangle type (fwd declared)

class BoundingSphere;
class Collidable;
class TerrainCell;

///
///	\ingroup OtherInternalGroup
///
class TerrainObject : public Drawable // replace with your appropriate class
{
private:
	GraphicsObject_TextureFlat* pGObjFT;				// Terrain
	GraphicsObject_WireframeConstantColor* pGObjFT2;	// Used for debugging this week

	int pixelWidth;
	int rowSize;
	int totalCells;
	float cellWidth;
	float baseDefault;
	Matrix scale;

	TerrainCell* cellsData;
	TerrainCell highlightedArea;
	
	CellIterator cellIt;

	///
	/// \brief Creates a Terrain Model from a heightmap
	///
	void CreateTerrainModel(const char* heightmapFile, int RepeatU, int RepeatV);
	///
	/// \brief Saves the Terrain Model to a file
	///
	void SaveTerrainModel( VertexStride_VUN* pVerts, int num_verts, TriangleIndex* tlist, int num_tri); 

	virtual void Draw() override;

	int GetVertIndex(int i, int j){ return j * pixelWidth + i; }
	int GetPixelIndex(int i, int j){ return 3 * (pixelWidth * (i + 1) - j - 1); }
	int GetCellDataIndex(int row, int col){ return row * (int)rowSize + col; }

	void pComputeGroupAABB(const BoundingSphere* cv);
	int GetRow(const Vect& v);
	int GetCol(const Vect& v);

public:
	TerrainObject(){};
	~TerrainObject();
	TerrainObject(const char* heightmapFile, float Sidelenght, float maxheight, float zeroHeight, char* TextureKey, int RepeatU, int RepeatV);

	///
	/// \brief Computes an AABB around the BoundingSphere for cell highlighting
	///
	/// \param cv The GameObject's BoundingSphere
	/// 
	void ComputeGroupAABB(const BoundingSphere* cv);
	///
	/// \brief Called by the user to draw the AABB of the TerrainCell under a GameObject
	///
	/// \param cv The GameObject's position
	/// 
	void HighlightCell(const Vect& p);
	///
	/// \brief Called by the user to draw the AABBs of TerrainCells under a GameObject
	///
	/// \param cv The GameObject's BoundingSphere
	/// 
	void HighlightCellArea(const BoundingSphere* cv);

	CellIterator SetCellIterator(TerrainCell& area);

	///
	/// \brief Returns the dimensions of the area that should be highlighted
	///
	const TerrainCell& GetHighlightedArea() const { return highlightedArea; }

	virtual Scene* GetGOScene() override;
};


#endif _TerrainObject