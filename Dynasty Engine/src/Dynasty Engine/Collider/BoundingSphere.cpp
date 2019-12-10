#include "BoundingSphere.h"
#include "..\Other Classes\MathTools.h"
#include "Visualizer.h"

void BoundingSphere::ComputeData(Model* mod, const Matrix& mat)
{
	Vect tempRadius = Vect(mod->radius, 0.0f, 0.0f, 0.0f) * mat;
	center = *mod->center * mat;
	radius = tempRadius.mag();
}

bool BoundingSphere::Intersect(BoundingSphere* other)
{
	return MathTools::Intersect(*this, *(other));
}

bool BoundingSphere::Intersect(AABB* other)
{
	return MathTools::Intersect(*this, *(other));
}

bool BoundingSphere::Intersect(OBB* other)
{
	return MathTools::Intersect(*this, *(other));
}

const Vect& BoundingSphere::GetCenter() const
{
	return center;
}

const float& BoundingSphere::GetRadius() const
{
	return radius;
}

Matrix& BoundingSphere::GetMatrix()
{
	Matrix scale;
	Matrix trans;

	scale.set(SCALE, radius, radius, radius);
	trans.set(TRANS, center);

	world = scale * trans;

	return world;
}