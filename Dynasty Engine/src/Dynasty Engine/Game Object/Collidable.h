#ifndef _Collidable
#define _Collidable

#include "AzulCore.h"
#include "..\Scene\Scene.h"
#include "..\Collider\CollisionVolume.h"
#include "..\Collider\BoundingSphere.h"

enum VolumeType;

///
///	\ingroup GameObjectGroup
///
class Collidable
{
private:
	virtual Scene* GetGOScene() = 0;

	Model* pModel;

	BoundingSphere* bSphere;

public:
	Collidable(){};
	~Collidable();
	Collidable(const Collidable&) = delete;
	Collidable& operator=(const Collidable&) = delete;

	CollisionVolume* cVolume = NULL;

	///
	///	\ingroup GameObjectGroup
	///
	/// \brief Use this function to program what you want to happen when a registered collision is detected
	///
	///	\param Collidable* Replace with whatever GameObject you are checking for collision with
	///
	/// \par Example:
	///
	///		This example shows the program outputting a message when a Cottage collides with a Spaceship
	///
	///		\code
	///		void Cottage::Collision(Spaceship*)
	///		{
	///			DebugMsg::out("Collision Cottage with Spaceship\n");
	///		}
	///		\endcode
	///
	virtual void Collision(Collidable*){};

	///
	/// \brief Use this function to program what you want to happen when a registered collision with the terrain
	///
	virtual void CollisionTerrain(){};

	///
	/// \brief Called when you want to register a GameObject for Collision
	///
	template <typename C>
	void CollisionRegistration(C* c)
	{
		GetGOScene()->RegisterCollision<C>(c);
	}

	///
	/// \brief Called when you want to deregister a GameObject for Collision
	///
	template <typename C>
	void CollisionDeregistration(C* c)
	{
		GetGOScene()->DeregisterCollision<C>(c);
	}

	static bool CollisionTestPair(Collidable* c1, Collidable* c2);

	///
	/// \brief Called to set the model for collision
	///
	/// \param mod The GameObject's model
	/// \param type What type of CollisionVolume you want EX: AABBtype
	/// 
	/// \par Example:
	///
	///		\code
	///		Cottage::Cottage()
	///		{
	///			SetColliderModel(pGObj_Cottage->getModel(), BStype);
	///		}
	///		\endcode
	///
	void SetColliderModel(Model* mod, VolumeType type);

	///
	/// \brief Called to update collision model, for when an object moves
	///
	/// \param mat The GameObject's world position
	///
	void UpdateCollisionData(const Matrix& mat);

	///
	/// \brief Returns the Colliadable's internal BoundingSphere
	///
	BoundingSphere* GetBSphere() { return bSphere; }
	///
	/// \brief Returns the Colliadable's internal CollisionVolume
	///
	CollisionVolume* GetCVolume() { return cVolume; }

};

#endif _Collidable