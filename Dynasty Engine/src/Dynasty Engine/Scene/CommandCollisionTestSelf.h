#ifndef _CommandCollisionTestSelf
#define _CommandCollisionTestSelf

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"

template <typename C>
class CommandCollisionTestSelf : public CommandBase
{
private:
	typename CollidableGroup<C>::CollidableCollection& Collection;

public:
	~CommandCollisionTestSelf<C>(){};
	CommandCollisionTestSelf<C>(const CommandCollisionTestSelf<C>&) = delete;
	CommandCollisionTestSelf<C>& operator=(const CommandCollisionTestSelf<C>&) = delete;

	CommandCollisionTestSelf<C>() : Collection(CollidableGroup<C>::GetColliderCollection()){};

	///
	/// \brief Go through the collection and test any of the contents are colliding
	///
	virtual void execute() override
	{
		for (auto it1 = Collection.begin(); it1 != Collection.end(); ++it1)
		{
			for (auto it2 = it1; it2 != Collection.end(); ++it2)
			{
				// BS1 with BS2
				if ((*it1)->GetBSphere()->Intersect((*it2)->GetBSphere()))
				{
					if (Collidable::CollisionTestPair((*it1), (*it2)))
					{
						if (it2 == it1)
							continue;

						(*it1)->Collision(*it2);
						(*it2)->Collision(*it1);

						(*it1)->GetCVolume()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
						(*it2)->GetCVolume()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
					}
				}
			}
		}
	}
};

#endif _CommandCollisionTestSelf