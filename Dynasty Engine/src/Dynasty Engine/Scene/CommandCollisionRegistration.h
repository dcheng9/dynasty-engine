#ifndef _CommandCollisionRegistration
#define _CommandCollisionRegistration

#include "CommandBase.h"
#include "..\Collider\CollidableGroup.h"

template <typename C>
class CommandCollisionRegistration : public CommandBase
{
public:
	C* ptrC;

	CommandCollisionRegistration<C>() = delete;
	~CommandCollisionRegistration<C>(){};
	CommandCollisionRegistration<C>(const CommandCollisionRegistration<C>&) = delete;
	CommandCollisionRegistration<C>& operator=(const CommandCollisionRegistration<C>&) = delete;

	CommandCollisionRegistration<C>(C* c) { ptrC = c; }

	virtual void execute() override
	{
		CollidableGroup<C>::Register(ptrC);
	}
};

#endif _CommandCollisionRegistration