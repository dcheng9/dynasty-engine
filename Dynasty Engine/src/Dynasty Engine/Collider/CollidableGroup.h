#ifndef _CollidableGroup
#define _CollidableGroup

#include <set>
#include "AzulCore.h"
#include "..\Scene\CommandCollisionDelete.h"
#include "AABB.h"
#include "BoundingSphere.h"
#include "Visualizer.h"

///
///	\ingroup OtherInternalGroup
///
template <typename C>
class CollidableGroup
{
public:
	typedef std::set<C*> CollidableCollection;

	///
	/// \brief Clears the CollidableGroup for deletion
	///
	static void Delete()
	{
		Instance().collideCol.clear();
		delete Instance().deleteCommand;
		delete Instance().internalAABB;

		delete singleInst;
		singleInst = NULL;
	}

	///
	/// \brief Erases a CollidableGroup from the collection
	///
	/// \param col The CollidableGroup you want to remove
	///
	static void Deregister(C* col)
	{
		Instance().collideCol.erase(col);
		DebugMsg::out("Deregistering Collision Group \n");
	}

	///
	/// \brief Adds a CollidableGroup to the collection
	///
	/// \param col The CollidableGroup you want to add
	///
	static void Register(C* col)
	{
		Instance().collideCol.insert(col);
		DebugMsg::out("Registering Collision Group \n");
	}

	///
	/// \brief Returns the CollidableGroup's internalAABB
	///
	static AABB* GetInternalAABB()
	{
		Instance().pUpdateAABB();
		return Instance().internalAABB;
	}

	///
	/// \brief Returns the CollidableGroup's collection
	///
	static CollidableCollection& GetColliderCollection()
	{
		return Instance().collideCol;
	}

	///
	/// \brief Returns the CollidableGroup's command for deletion
	///
	static CommandBase* GetShutdownCommand()
	{
		return Instance().deleteCommand;
	}

private:
	CollidableGroup<C>()
	{
		deleteCommand = new CommandCollisionDelete<C>(); 
		internalAABB = new AABB(); 
		Visualizer::Register(internalAABB, Vect(0.0f, 0.0f, 0.0f, 0.0f));
	}
	virtual ~CollidableGroup<C>(){ singleInst = nullptr; }
	CollidableGroup<C>(const CollidableGroup<C>&) = delete;
	CollidableGroup<C>& operator=(const CollidableGroup<C>&) = delete;

	static CollidableGroup<C>* singleInst;

	AABB* internalAABB;

	static CollidableGroup& Instance()
	{
		if (!singleInst)
			singleInst = new CollidableGroup<C>();
		return *singleInst;
	};

	CollidableCollection collideCol;
	CommandCollisionDelete<C>* deleteCommand;

	void pUpdateAABB()
	{
		Vect minVertex = (*collideCol.begin())->GetBSphere()->GetCenter();
		Vect maxVertex = (*collideCol.begin())->GetBSphere()->GetCenter();

		for (auto it = collideCol.begin(); it != collideCol.end(); it++)
		{
			Vect center = (*it)->GetBSphere()->GetCenter();
			float radius = (*it)->GetBSphere()->GetRadius();

			Vect tempMin = Vect(center.X() - radius, center.Y() - radius, center.Z() - radius);
			Vect tempMax = Vect(center.X() + radius, center.Y() + radius, center.Z() + radius);

			minVertex.X() = min(tempMin.X(), minVertex.X());
			maxVertex.X() = max(tempMax.X(), maxVertex.X());
			minVertex.Y() = min(tempMin.Y(), minVertex.Y());
			maxVertex.Y() = max(tempMax.Y(), maxVertex.Y());
			minVertex.Z() = min(tempMin.Z(), minVertex.Z());
			maxVertex.Z() = max(tempMax.Z(), maxVertex.Z());
		}

		internalAABB->ComputeGroupAABB(minVertex, maxVertex);
	}
};

template <typename C>
CollidableGroup<C>* CollidableGroup<C>::singleInst = 0;

#endif _CollidableGroup