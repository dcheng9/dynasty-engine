#ifndef _BoundingSphere
#define _BoundingSphere

#include "AzulCore.h"
#include "CollisionVolume.h"

class AABB;
class OBB;

///
///	\ingroup UsefulTools
///
class BoundingSphere : public CollisionVolume
{
private:
	Vect center;
	float radius;
	Matrix world;

public:
	BoundingSphere(){ vType = BStype; };
	virtual ~BoundingSphere(){};
	BoundingSphere(const BoundingSphere&) = delete;
	BoundingSphere& operator=(const BoundingSphere&) = delete;

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
	/// \brief Returns the BoundingSphere's center
	///
	virtual const Vect& GetCenter() const;
	///
	/// \brief Returns the BoundingSphere's radius
	///
	virtual const float& GetRadius() const;
	///
	/// \brief Returns a CollisionVolume's world for the Visualizer
	///
	virtual Matrix& GetMatrix() override;
};

#endif _BoundingSphere