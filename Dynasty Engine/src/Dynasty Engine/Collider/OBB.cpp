#include "OBB.h"
#include "..\Other Classes\MathTools.h"
#include "Visualizer.h"

OBB::~OBB()
{
}

void OBB::ComputeData(Model* mod, const Matrix& mat)
{
	OBBMin = *mod->minPointAABB;
	OBBMax = *mod->maxPointAABB;
	OBBCenter = OBBMax + ((OBBMin - OBBMax) * 0.5f);
	halfDiag = (OBBMax - OBBMin) * 0.5f;
	halfDiag.W() = 0.0f;

	world = mat;
	OBBCenter *= world;
	scaleFactor = (Vect(1.0f, 0.0f, 0.0f, 0.0f) * world).magSqr();
}

bool OBB::Intersect(BoundingSphere* other)
{
	return MathTools::Intersect(*(other), *this);
}

bool OBB::Intersect(AABB* other)
{
	return MathTools::Intersect(*this, *(other));
}

bool OBB::Intersect(OBB* other)
{
	return MathTools::Intersect(*this, *(other));
}

const Vect OBB::GetOBBMin() const
{
	return OBBMin;
}

const Vect OBB::GetOBBMax() const
{
	return OBBMax;
}

const Vect OBB::GetCenter() const
{
	return OBBCenter;
}

const Vect OBB::GetDiag() const
{
	return halfDiag;
}

const float OBB::GetScaleFactor() const
{
	return scaleFactor;
}

const Matrix OBB::GetWorld() const
{
	return world;
}

Matrix& OBB::GetMatrix()
{
	Matrix scale;
	Matrix trans;

	scale.set(SCALE, OBBMax - OBBMin);
	trans.set(TRANS, 0.5f * (OBBMax + OBBMin));

	worldMat = scale * trans;
	worldMat *= world;

	return worldMat;
}