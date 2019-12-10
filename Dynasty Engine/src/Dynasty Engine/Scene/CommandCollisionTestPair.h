#ifndef _CommandCollisionTestPair
#define _CommandCollisionTestPair

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"
#include "..\Collider\Visualizer.h"

template <typename C1, typename C2>
class CommandCollisionTestPair : public CommandBase
{
private:
	typename CollidableGroup<C1>::CollidableCollection& Collection1;
	typename CollidableGroup<C2>::CollidableCollection& Collection2;

public:
	~CommandCollisionTestPair<C1, C2>(){};
	CommandCollisionTestPair<C1, C2>(const CommandCollisionTestPair<C1, C2>&) = delete;
	CommandCollisionTestPair<C1, C2>& operator=(const CommandCollisionTestPair<C1, C2>&) = delete;

	CommandCollisionTestPair<C1, C2>() : Collection1(CollidableGroup<C1>::GetColliderCollection()),
										 Collection2(CollidableGroup<C2>::GetColliderCollection()){};
	///
	/// \brief Go through both collections and test any of the contents are colliding
	///
	virtual void execute() override
	{
		// CG1 with CG2
		if (CollidableGroup<C1>::GetInternalAABB()->Intersect(CollidableGroup<C2>::GetInternalAABB()))
		{
			CollidableGroup<C1>::GetInternalAABB()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
			CollidableGroup<C2>::GetInternalAABB()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));

			for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
			{

				// BS1 with CG2
				if ((*it1)->GetBSphere()->Intersect(CollidableGroup<C2>::GetInternalAABB()))
				{
					(*it1)->GetBSphere()->CollidingOn(Vect(0.0f, 1.0f, 0.0f, 0.0f));

					for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
					{

						// BS2 with CG1
						if ((*it2)->GetBSphere()->Intersect(CollidableGroup<C1>::GetInternalAABB()))
						{
							(*it2)->GetBSphere()->CollidingOn(Vect(0.0f, 1.0f, 0.0f, 0.0f));

							// BS1 with BS2
							if ((*it1)->GetBSphere()->Intersect((*it2)->GetBSphere()))
							{
								(*it1)->GetBSphere()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
								(*it2)->GetBSphere()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));

								// CV1 with CV2
								if ((*it1)->CollisionTestPair(*it1, *it2))
								{
									(*it2)->Collision(*it1);
									(*it1)->Collision(*it2);

									(*it1)->GetCVolume()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
									(*it2)->GetCVolume()->CollidingOn(Vect(1.0f, 0.0f, 0.0f, 0.0f));
								}
							}
						}
					}
				}
			}
		}
	}
};

#endif _CommandCollisionTestPair