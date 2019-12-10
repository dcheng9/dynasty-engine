#ifndef _CommandCollisionDeregistration
#define _CommandCollisionDeregistration

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"

template <typename C>
class CommandCollisionDeregistration : public CommandBase
{
public:
	C* ptrC;

	CommandCollisionDeregistration<C>() = delete;
	~CommandCollisionDeregistration<C>(){};
	CommandCollisionDeregistration<C>(const CommandCollisionDeregistration<C>&) = delete;
	CommandCollisionDeregistration<C>& operator=(const CommandCollisionDeregistration<C>&) = delete;

	CommandCollisionDeregistration<C>(C* c) { ptrC = c; }

	virtual void execute() override
	{
		CollidableGroup<C>::Deregister(ptrC);
	}
};

#endif _CommandCollisionDeregistration