#ifndef _CollisionManager
#define _CollisionManager

#include <set>
#include "AzulCore.h"
#include "..\Scene\CommandCollisionTestPair.h"
#include "..\Scene\CommandCollisionTestSelf.h"
#include "..\Scene\CommandCollisionTestTerrain.h"

class Collidable;

///
///	\ingroup GameObjectManagerGroup
///
class CollisionManager
{
private:
	typedef std::set<CommandBase*> CommandSet;
	CommandSet colTestCommands;
	CommandSet colDeleteCommands;

public:
	CollisionManager(){};
	~CollisionManager();
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	///
	/// \brief Iterate through the set and call execute on each item
	///
	void ProcessCollisions();
	///
	/// \brief Gets a CollidableGroup's delete command and adds it to a set
	///
	void AddColGroupDeleteCommand(CommandBase* c);
	///
	/// \brief Clears the manager for deletion
	///
	void Delete();

	///
	/// \brief Create a command to check for collision between a pair
	///
	template <typename C1, typename C2>
	void SetCollisionPair()
	{
		CommandCollisionTestPair<C1, C2> *ptrClCmd = new CommandCollisionTestPair<C1, C2>();
		colTestCommands.insert(ptrClCmd);
	}

	///
	/// \brief Create a command to check for collision between a two of the same GameObjects
	///
	template <typename C>
	void SetCollisionSelf()
	{
		CommandCollisionTestSelf<C> *ptrClCmd = new CommandCollisionTestSelf<C>();
		colTestCommands.insert(ptrClCmd);
	}

	///
	/// \brief Create a command to check for collision between a GameObject and the TerrainObject
	///
	template <typename C>
	void SetCollisionTerrain()
	{
		CommandCollisionTestTerrain<C> *ptrClCmd = new CommandCollisionTestTerrain<C>();
		colTestCommands.insert(ptrClCmd);
	}
};

#endif _CollisionManager