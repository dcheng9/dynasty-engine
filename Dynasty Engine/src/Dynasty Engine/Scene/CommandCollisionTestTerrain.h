#ifndef _CommandCollisionTestTerrain
#define _CommandCollisionTestTerrain

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"
#include "..\Terrain\TerrainObject.h"
#include "..\Terrain\TerrainCell.h"
#include "..\Collider\AABB.h"
#include "..\Managers\SceneManager.h"
#include "..\Other Classes\MathTools.h"
#include "..\Terrain\CellIterator.h"

template <typename C>
class CommandCollisionTestTerrain : public CommandBase
{
private:
	typename CollidableGroup<C>::CollidableCollection& Collection;

public:
	~CommandCollisionTestTerrain<C>(){};
	CommandCollisionTestTerrain<C>(const CommandCollisionTestTerrain<C>&) = delete;
	CommandCollisionTestTerrain<C>& operator=(const CommandCollisionTestTerrain<C>&) = delete;

	CommandCollisionTestTerrain<C>() : Collection(CollidableGroup<C>::GetColliderCollection()){};

	///
	/// \brief Go through the collection and test any of the contents are colliding with the TerrainObject
	///
	virtual void execute() override
	{
		TerrainObject* pTerrain = SceneManager::GetCurrentTerrain();
		AABB CellAABB;

		for (auto it1 = Collection.begin(); it1 != Collection.end(); it1++)
		{
			// Computes an invisible AABB from the BSphere of the current object
			pTerrain->ComputeGroupAABB((*it1)->GetBSphere());
			// These are the cells under that invisible AABB
			TerrainCell highlightedArea;
			highlightedArea = pTerrain->GetHighlightedArea();

			CellIterator Cells = pTerrain->SetCellIterator(highlightedArea);

			// Iterate through the highlightedArea
			for (CellIterator it2 = Cells.begin(); it2 <= Cells.end(); it2++)
			{
				CellAABB.ComputeGroupAABB((*it2).GetMinCorner(), (*it2).GetMaxCorner());

				// Cells with BS
				if (CellAABB.Intersect((*it1)->GetBSphere()))
				{
					(it2).CollidingOn(Vect(0.0f, 1.0f, 0.0f, 0.0f));
					(*it1)->GetBSphere()->CollidingOn(Vect(0.0f, 1.0f, 0.0f, 0.0f));

					// Cells with CV
					if (CellAABB.Intersect((*it1)->GetCVolume()))
					{
						(*it1)->GetBSphere()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
						(*it1)->GetCVolume()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
						(it2).CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));

						(*it1)->CollisionTerrain();
					}


				}
			}
		}
	}
};

#endif _CommandCollisionTestTerrain