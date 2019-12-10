#include "CollisionManager.h"

#include "..\Game Object\Collidable.h"

CollisionManager::~CollisionManager()
{
	colTestCommands.clear();

	for (CommandSet::iterator it = colDeleteCommands.begin(); it != colDeleteCommands.end(); it++)
	{
		(*it)->execute();
	}

	colDeleteCommands.clear();
}

void CollisionManager::ProcessCollisions()
{
	for (CommandSet::iterator it = colTestCommands.begin(); it != colTestCommands.end(); it++)
	{
		(*it)->execute();
	}
}

void CollisionManager::AddColGroupDeleteCommand(CommandBase* c)
{
	colDeleteCommands.insert(c);
}

void CollisionManager::Delete()
{
	colTestCommands.clear();

	for (CommandSet::iterator it = colDeleteCommands.begin(); it != colDeleteCommands.end(); it++)
	{
		(*it)->execute();
	}

	colDeleteCommands.clear();

	DebugMsg::out("Collision Manager Deleted \n");
}
