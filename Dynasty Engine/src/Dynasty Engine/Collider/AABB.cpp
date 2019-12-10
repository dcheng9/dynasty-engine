#include "AABB.h"
#include "..\Other Classes\MathTools.h"
#include "Visualizer.h"

void AABB::ComputeData(Model* mod, const Matrix& mat)
{
	Vect* vList = mod->getVectList();
	AABBMin = vList[0] * mat;
	AABBMax = vList[0] * mat;

	for (int i = 0; i < mod->numVerts; i++)
	{
		Vect temp = vList[i] * mat;
		AABBMin.X() = min(temp.X(), AABBMin.X());
		AABBMin.Y() = min(temp.Y(), AABBMin.Y());
		AABBMin.Z() = min(temp.Z(), AABBMin.Z());

		AABBMax.X() = max(temp.X(), AABBMax.X());
		AABBMax.Y() = max(temp.Y(), AABBMax.Y());
		AABBMax.Z() = max(temp.Z(), AABBMax.Z());
	}

	halfDiag = (AABBMax - AABBMin) * 0.5f;
	halfDiag.W() = 0.0f;
	AABBCenter = AABBMin + halfDiag;

	world = mat;
	scaleFactor = (Vect(1.0f, 0.0f, 0.0f, 0.0f) * world).magSqr();
}

void AABB::ComputeGroupAABB(const Vect& groupMin, const Vect& groupMax)
{
	AABBMin = groupMin;
	AABBMax = groupMax;
}

bool AABB::Intersect(BoundingSphere* other)
{
	return MathTools::Intersect(*(other), *this);
}

bool AABB::Intersect(AABB* other)
{
	return MathTools::Intersect(*this, *(other));
}

bool AABB::Intersect(OBB* other)
{
	return MathTools::Intersect(*(other), *this);
}

const Vect AABB::GetAABBMin() const
{
	return AABBMin;
}

const Vect AABB::GetAABBMax() const
{
	return AABBMax;
}

const Vect AABB::GetCenter() const
{
	return AABBCenter;
}

const Vect AABB::GetDiag() const
{
	return halfDiag;
}

const float AABB::GetScaleFactor() const
{
	return scaleFactor;
}

const Matrix AABB::GetWorld() const
{
	return world;
}

Matrix& AABB::GetMatrix()
{
	Matrix scale;
	Matrix trans;

	scale.set(SCALE, AABBMax - AABBMin);
	trans.set(TRANS, 0.5f * (AABBMax + AABBMin));

	worldMat = scale * trans;

	return worldMat;
}