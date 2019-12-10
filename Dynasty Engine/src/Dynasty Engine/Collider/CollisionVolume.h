#ifndef _CollisionVolume
#define _CollisionVolume

#include "AzulCore.h"

class BoundingSphere;
class AABB;
class OBB;

enum VolumeType { BStype = 0, AABBtype = 1, OBBtype = 2 };

///
///	\ingroup OtherInternalGroup
///
class CollisionVolume
{
public:
	virtual ~CollisionVolume(){};
	CollisionVolume(){};
	CollisionVolume(const CollisionVolume&) = delete;
	CollisionVolume& operator=(const CollisionVolume&) = delete;

	VolumeType vType;
	Matrix world;
	bool isColliding = false;
	Vect collidingColor = Vect(0.0f, 0.0f, 0.0f, 0.0f);

	///
	/// \brief Computes a models center and radius 
	///
	virtual void ComputeData(Model* mod, const Matrix& mat){ mod; mat; };
	///
	/// \brief Double dispatch for CollisionVolumes
	///
	virtual bool Intersect(CollisionVolume* other){ other; return false; }
	///
	/// \brief Calls MathTools to Intersect to see if the CollisionVolume intersects with a BoundingSphere
	///
	virtual bool Intersect(BoundingSphere* other){ other; return false; }
	///
	/// \brief Calls MathTools to Intersect to see if the CollisionVolume intersects with a AABB
	///
	virtual bool Intersect(AABB* other){ other; return false; }
	///
	/// \brief Calls MathTools to Intersect to see if the CollisionVolume intersects with a OBB
	///
	virtual bool Intersect(OBB* other){ other; return false; }
	///
	/// \brief Returns a CollisionVolume's world for the Visualizer
	///
	virtual Matrix& GetMatrix(){ return world; }
	///
	/// \brief Toggles the CollisionVolume to be colliding
	///
	virtual void CollidingOn(const Vect& col){ isColliding = true; collidingColor = col; }
	///
	/// \brief Toggles the CollisionVolume to not be colliding
	///
	virtual void CollidingOff(){ isColliding = false; }
	///
	/// \brief Returns whether a CollisionVolume is colliding or not
	///
	virtual bool CheckColliding(){ return isColliding; }
	///
	/// \brief Returns a CollisionVolume's collision color
	///
	virtual Vect GetCollidingColor(){ return collidingColor; }
};

#endif _CollisionVolume