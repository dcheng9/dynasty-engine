#ifndef _AABB
#define _AABB

#include "AzulCore.h"
#include "CollisionVolume.h"

class BoundingSphere;
class OBB;

///
///	\ingroup UsefulTools
///
class AABB : public CollisionVolume
{
private:
	Vect AABBMin;
	Vect AABBMax;
	Vect AABBCenter;
	Vect halfDiag;

	float scaleFactor;

	Matrix worldMat;

public:
	AABB(){ vType = AABBtype; };
	virtual ~AABB(){};
	AABB(const AABB&) = delete;
	AABB& operator=(const AABB&) = delete;

	///
	/// \brief Computes a models center and matrix details
	///
	virtual void ComputeData(Model* mod, const Matrix& mat) override;
	///
	/// \brief Computes a CollidableGroup's internalAABB
	///
	virtual void ComputeGroupAABB(const Vect& groupMin, const Vect& groupMax);
	///
	/// \brief Double dispatch for CollisionVolumes
	///
	virtual bool Intersect(CollisionVolume* other) override { return other->Intersect(this); }
	///
	/// \brief Calls MathTools to Intersect to see if an OBB and a BoundingSphere intersect
	///
	virtual bool Intersect(BoundingSphere* other) override;
	///
	/// \brief Calls MathTools to Intersect to see if an OBB and a AABB intersect
	///
	virtual bool Intersect(AABB* other) override;
	///
	/// \brief Calls MathTools to Intersect to see if two OBBs intersect
	///
	virtual bool Intersect(OBB* other) override;
	///
	/// \brief Gets the AABB minimum
	///
	virtual const Vect GetAABBMin() const;
	///
	/// \brief Gets the AABB maximum
	///
	virtual const Vect GetAABBMax() const;
	///
	/// \brief Gets the AABB center
	///
	virtual const Vect GetCenter() const;
	///
	/// \brief Gets the AABB diagonal
	///
	virtual const Vect GetDiag() const;
	///
	/// \brief Gets the scale factor
	///
	virtual const float GetScaleFactor() const;
	///
	/// \brief Gets the world matrix
	///
	virtual const Matrix GetWorld() const;
	///
	/// \brief Returns a CollisionVolume's world for the Visualizer
	///
	virtual Matrix& GetMatrix() override;
};

#endif _AABB