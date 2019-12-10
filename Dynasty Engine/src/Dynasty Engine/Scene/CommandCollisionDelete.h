#ifndef _CommandCollisionDelete
#define _CommandCollisionDelete

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"

template <typename C>
class CommandCollisionDelete : public CommandBase
{
public:
	CommandCollisionDelete<C>(){};
	~CommandCollisionDelete<C>(){};
	CommandCollisionDelete<C>(const CommandCollisionDelete<C>&) = delete;
	CommandCollisionDelete<C>& operator=(const CommandCollisionDelete<C>&) = delete;

	virtual void execute() override
	{
		CollidableGroup<C>::Delete();
	}
};

#endif _CommandCollisionDelete