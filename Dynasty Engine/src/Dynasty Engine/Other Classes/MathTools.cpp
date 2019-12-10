#include "MathTools.h"
#include "..\Collider\BoundingSphere.h"
#include "..\Collider\AABB.h"
#include "..\Collider\OBB.h"
#include "..\Terrain\TerrainObject.h"
#include "..\Terrain\TerrainCell.h"

bool MathTools::Intersect(const BoundingSphere& a, const BoundingSphere& b)
{
	// Check if BoundingSpheres are touching
	if ((a.GetCenter() - b.GetCenter()).magSqr() < pow((a.GetRadius() + b.GetRadius()), 2))
		return true;
	else
		return false;
}

bool MathTools::Intersect(const AABB& a, const AABB& b)
{
	return AABBCheckOverlap(a, b);
}

bool MathTools::Intersect(const BoundingSphere& a, const AABB& b)
{
	Vect center = a.GetCenter();

	// Get closest point to the BoundingSphere
	center.X() = ClampAABB(center.X(), b.GetAABBMin().X(), b.GetAABBMax().X());
	center.Y() = ClampAABB(center.Y(), b.GetAABBMin().Y(), b.GetAABBMax().Y());
	center.Z() = ClampAABB(center.Z(), b.GetAABBMin().Z(), b.GetAABBMax().Z());

	return PointIntersectSphere(center, a);
}

bool MathTools::Intersect(const BoundingSphere& a, const OBB& b)
{
	Vect center = a.GetCenter();

	center *= b.GetWorld().getInv();

	// Get closest point to the BoundingSphere
	center.X() = ClampAABB(center.X(), b.GetOBBMin().X(), b.GetOBBMax().X());
	center.Y() = ClampAABB(center.Y(), b.GetOBBMin().Y(), b.GetOBBMax().Y());
	center.Z() = ClampAABB(center.Z(), b.GetOBBMin().Z(), b.GetOBBMax().Z());

	center *= b.GetWorld();

	return PointIntersectSphere(center, a);
}

bool MathTools::Intersect(const OBB& a, const OBB& b)
{
	Vect axis[15];
	
	axis[0] = a.GetWorld().get(ROW_0);
	axis[0].W() = 0.0f;
	axis[1] = a.GetWorld().get(ROW_1);
	axis[1].W() = 0.0f;
	axis[2] = a.GetWorld().get(ROW_2);
	axis[2].W() = 0.0f;
	axis[3] = b.GetWorld().get(ROW_0);
	axis[3].W() = 0.0f;
	axis[4] = b.GetWorld().get(ROW_1);
	axis[4].W() = 0.0f;
	axis[5] = b.GetWorld().get(ROW_2);
	axis[5].W() = 0.0f;
	axis[6] = axis[0].cross(axis[3]);
	axis[6].W() = 0.0f;
	axis[7] = axis[0].cross(axis[4]);
	axis[7].W() = 0.0f;
	axis[8] = axis[0].cross(axis[5]);
	axis[8].W() = 0.0f;
	axis[9] = axis[1].cross(axis[3]);
	axis[9].W() = 0.0f;
	axis[10] = axis[1].cross(axis[4]);
	axis[10].W() = 0.0f;
	axis[11] = axis[1].cross(axis[5]);
	axis[11].W() = 0.0f;
	axis[12] = axis[2].cross(axis[3]);
	axis[12].W() = 0.0f;
	axis[13] = axis[2].cross(axis[4]);
	axis[13].W() = 0.0f;
	axis[14] = axis[2].cross(axis[5]);
	axis[14].W() = 0.0f;

	// Go through and get all of the axes
	for (int i = 0; i < 15; i++)
	{
		if (axis[i].magSqr() > FLT_EPSILON)
		{
			if (!OBBCheckOverlap(axis[i], a, b))
				return false;
		}
	}
	return true;
}

bool MathTools::Intersect(const OBB& a, const AABB& b)
{
	Vect axis[15];

	axis[0] = a.GetWorld().get(ROW_0);
	axis[0].W() = 0.0f;
	axis[1] = a.GetWorld().get(ROW_1);
	axis[1].W() = 0.0f;
	axis[2] = a.GetWorld().get(ROW_2);
	axis[2].W() = 0.0f;
	axis[3] = b.GetWorld().get(ROW_0);
	axis[3].W() = 0.0f;
	axis[4] = b.GetWorld().get(ROW_1);
	axis[4].W() = 0.0f;
	axis[5] = b.GetWorld().get(ROW_2);
	axis[5].W() = 0.0f;
	axis[6] = axis[0].cross(axis[3]);
	axis[6].W() = 0.0f;
	axis[7] = axis[0].cross(axis[4]);
	axis[7].W() = 0.0f;
	axis[8] = axis[0].cross(axis[5]);
	axis[8].W() = 0.0f;
	axis[9] = axis[1].cross(axis[3]);
	axis[9].W() = 0.0f;
	axis[10] = axis[1].cross(axis[4]);
	axis[10].W() = 0.0f;
	axis[11] = axis[1].cross(axis[5]);
	axis[11].W() = 0.0f;
	axis[12] = axis[2].cross(axis[3]);
	axis[12].W() = 0.0f;
	axis[13] = axis[2].cross(axis[4]);
	axis[13].W() = 0.0f;
	axis[14] = axis[2].cross(axis[5]);
	axis[14].W() = 0.0f;

	// Go through and get all of the axes
	for (int i = 0; i < 15; i++)
	{
		if (axis[i].magSqr() > FLT_EPSILON)
		{
			if (!OBBCheckOverlap(axis[i], a, b))
				return false;
		}
	}
	return true;
}

bool MathTools::AABBCheckOverlap(const AABB& a, const AABB& b)
{
	Vect minA = a.GetAABBMin();
	Vect maxA = a.GetAABBMax();

	Vect minB = b.GetAABBMin();
	Vect maxB = b.GetAABBMax();

	// Check all sides for corner overlap
	bool xIntersect = IntervalOverlap(minA.X(), maxA.X(), minB.X(), maxB.X());
	bool yIntersect = IntervalOverlap(minA.Y(), maxA.Y(), minB.Y(), maxB.Y());
	bool zIntersect = IntervalOverlap(minA.Z(), maxA.Z(), minB.Z(), maxB.Z());

	if (xIntersect && yIntersect && zIntersect)
		return true;
	else
		return false;
}

bool MathTools::IntervalOverlap(float a, float b, float c, float d)
{
	// Check for corner overlap
	if ((b < c) || (d < a))
		return false;
	else
		return true;
}

bool MathTools::PointIntersectSphere(Vect& p, const BoundingSphere& s)
{
	// Check for a point inside a Sphere's radius
	if ((p - s.GetCenter()).mag() <= s.GetRadius())
		return true;
	else
		return false;
}

float MathTools::ClampAABB(float i, float min, float max)
{
	// Restrict a point to a min and max
	if (i < min)
		return min;
	else if (i > max)
		return max;
	else
		return i;
}

bool MathTools::OBBCheckOverlap(const Vect& v, const OBB& a, const OBB& b)
{
	// THIS WORKS MOSTLY
	//Vect diff = a.GetCenter() - b.GetCenter();
	//diff.W() = 0.0f;
	
	float distance = MaxProjectionDist(v, a, b);
	//float distance2 = (diff.dot(v) / v.mag());

	if (distance <= (MaxProjection(v, a) + MaxProjection(v, b)))
	{
		return true;
	}
	else
		return false;
}

bool MathTools::OBBCheckOverlap(const Vect& v, const OBB& a, const AABB& b)
{
	float distance = MaxProjectionDist(v, a, b);

	if (distance <= (MaxProjection(v, a) + MaxProjection(v, b)))
	{
		return true;
	}
	else
		return false;
}

float MathTools::MaxProjectionDist(const Vect& v, const OBB& a, const OBB& b)
{
	Vect c = a.GetCenter() - b.GetCenter();
	c.W() = 0.0f;

	// Dot product
	float maxProj = v.X() * c.X() + v.Y() * c.Y() + v.Z() * c.Z();

	return (maxProj / v.mag());
}

float MathTools::MaxProjectionDist(const Vect& v, const OBB& a, const AABB& b)
{
	Vect c = a.GetCenter() - b.GetCenter();
	c.W() = 0.0f;

	// Dot product
	float maxProj = v.X() * c.X() + v.Y() * c.Y() + v.Z() * c.Z();

	return (maxProj / v.mag());
}

//float MathTools::MaxProjectionDist(const Vect& v, const OBB& a, const OBB& b)
//{
//	const Vect& vTemp = v * a.GetWorld().getInv();
//	Vect c = a.GetCenter() - b.GetCenter();
//	c.W() = 0.0f;
//
//	float maxProj = abs(vTemp.X() * c.X()) + abs(vTemp.Y() * c.Y()) + abs(vTemp.Z() * c.Z());
//
//	return (maxProj / v.mag()) * a.GetScaleFactor() / 2;
//}

float MathTools::MaxProjection(const Vect& v, const OBB& a)
{
	const Vect& vTemp = v * a.GetWorld().getInv();
	const Vect& diag = a.GetDiag();

	// Dot product
	float maxProj = abs(vTemp.X() * diag.X()) + abs(vTemp.Y() * diag.Y()) + abs(vTemp.Z() * diag.Z());

	// Scale the projection
	return ((maxProj / v.mag()) * a.GetScaleFactor());
}

float MathTools::MaxProjection(const Vect& v, const AABB& a)
{
	const Vect& vTemp = v * a.GetWorld().getInv();
	const Vect& diag = a.GetDiag();

	// Dot product
	float maxProj = abs(vTemp.X() * diag.X()) + abs(vTemp.Y() * diag.Y()) + abs(vTemp.Z() * diag.Z());

	// Scale the projection
	return ((maxProj / v.mag()) * a.GetScaleFactor());
}