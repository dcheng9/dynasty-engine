#ifndef _OBB
#define _OBB

#include "CollisionVolume.h"

class BoundingSphere;

///
///	\ingroup UsefulTools
///
class OBB : public CollisionVolume
{
private:
	Vect OBBMin;
	Vect OBBMax;
	Vect OBBCenter;
	Vect halfDiag;

	float scaleFactor;

	Matrix worldMat;

public:
	OBB(){ vType = OBBtype; };
	virtual ~OBB();
	OBB(const OBB&) = delete;
	OBB& operator=(const OBB&) = delete;

	///
	/// \brief Computes a models center and radius 
	///
	virtual void ComputeData(Model* mod, const Matrix& mat) override;
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
	/// \brief Gets the OBB minimum
	///
	virtual const Vect GetOBBMin() const;
	///
	/// \brief Gets the OBB maximum
	///
	virtual const Vect GetOBBMax() const;
	///
	/// \brief Gets the OBB center
	///
	virtual const Vect GetCenter() const;
	///
	/// \brief Gets the OBB diagonal
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

#endif _OBB