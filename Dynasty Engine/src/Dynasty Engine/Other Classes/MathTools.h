#ifndef _MathTools
#define _MathTools

#include <math.h>
#include "AzulCore.h"

class BoundingSphere;
class AABB;
class OBB;
class TerrainCell;

///
///	\ingroup OtherInternalGroup
///
class MathTools
{
public:
	MathTools();
	~MathTools(){};
	MathTools(const MathTools&) = delete;
	MathTools& operator=(const MathTools&) = delete;

	static bool Intersect(const BoundingSphere& a, const BoundingSphere& b);
	static bool Intersect(const AABB& a, const AABB& b);
	static bool Intersect(const BoundingSphere& a, const AABB& b);
	static bool Intersect(const BoundingSphere& a, const OBB& b);
	static bool Intersect(const OBB& a, const OBB& b);
	static bool Intersect(const OBB& a, const AABB& b);

	static bool AABBCheckOverlap(const AABB& a, const AABB& b);

	static bool IntervalOverlap(float a, float b, float c, float d);
	static bool PointIntersectSphere(Vect& p, const BoundingSphere& s);
	static float ClampAABB(float i, float min, float max);

	static bool OBBCheckOverlap(const Vect& v, const OBB& a, const OBB& b);
	static bool OBBCheckOverlap(const Vect& v, const OBB& a, const AABB& b);
	static float MaxProjectionDist(const Vect& v, const OBB& a, const OBB& b);
	static float MaxProjectionDist(const Vect& v, const OBB& a, const AABB& b);
	static float MaxProjection(const Vect& v, const OBB& a);
	static float MaxProjection(const Vect& v, const AABB& a);
};

#endif _MathTools