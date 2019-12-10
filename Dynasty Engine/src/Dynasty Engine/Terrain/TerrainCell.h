#ifndef _TerrainCell
#define _TerrainCell

#include "AzulCore.h"

///
///	\ingroup OtherInternalGroup
///
class TerrainCell
{
private:
	Vect minCorner;
	Vect maxCorner;
	int xIndex;
	int yIndex;

	bool isColliding = false;
	Vect collidingColor = Vect(0.0f, 0.0f, 0.0f, 0.0f);

public:
	virtual ~TerrainCell(){};
	TerrainCell(){};
	TerrainCell(const TerrainCell&);

	///
	/// \brief Sets the TerrainCell's minCorner
	///
	void SetMinCorner(const Vect& minC){ minCorner = minC; }
	///
	/// \brief Sets the TerrainCell's maxCorner
	///
	void SetMaxCorner(const Vect& maxC){ maxCorner = maxC; }
	///
	/// \brief Sets the TerrainCell's xIndex
	///
	void SetXIndex(int index){ xIndex = index; }
	///
	/// \brief Sets the TerrainCell's yIndex
	///
	void SetYIndex(int index){ yIndex = index; }
	///
	/// \brief Returns the TerrainCell's minCorner
	///
	const Vect GetMinCorner() const { return minCorner; }
	///
	/// \brief Returns the TerrainCell's maxCorner
	///
	const Vect GetMaxCorner() const { return maxCorner; }
	///
	/// \brief Returns the TerrainCell's xIndex
	///
	const int GetXIndex() const { return xIndex; }
	///
	/// \brief Returns the TerrainCell's xIndex
	///
	const int GetYIndex() const { return yIndex; }
	///
	/// \brief Toggles the TerrainCell to be colliding
	///
	void CollidingOn(const Vect& col){ isColliding = true; collidingColor = col; }
	///
	/// \brief Toggles the TerrainCell to not be colliding
	///
	void CollidingOff(){ isColliding = false; }
	///
	/// \brief Returns whether a TerrainCell is colliding or not
	///
	bool CheckColliding(){ return isColliding; }
	///
	/// \brief Returns a TerrainCell's collision color
	///
	Vect GetCollidingColor(){ return collidingColor; }
};
#endif _TerrainCell