#include "Collidable.h"
#include "..\Collider\CollisionVolume.h"
#include "..\Collider\AABB.h"
#include "..\Collider\OBB.h"

Collidable::~Collidable()
{
	if (cVolume != NULL)
	{
		delete cVolume;
	}
}

bool Collidable::CollisionTestPair(Collidable *c1, Collidable *c2)
{
	return c1->cVolume->Intersect(c2->cVolume);
}

void Collidable::SetColliderModel(Model *mod, VolumeType type)
{
	pModel = mod;

	switch (type)
	{
	case BStype:
		cVolume = new BoundingSphere();
		break;
	case AABBtype:
		cVolume = new AABB();
		break;
	case OBBtype:
		cVolume = new OBB();
		break;
	default:
		break;
	}

	bSphere = new BoundingSphere();
}

void Collidable::UpdateCollisionData(const Matrix& mat)
{
	cVolume->ComputeData(pModel, mat);
	bSphere->ComputeData(pModel, mat);
}