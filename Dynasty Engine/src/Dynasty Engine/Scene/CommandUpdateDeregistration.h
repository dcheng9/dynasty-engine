#ifndef _CommandUpdateDeregistration
#define _CommandUpdateDeregistration

#include "CommandBase.h"
#include "..\Managers\UpdatableManager.h"

class CommandUpdateDeregistration : public CommandBase
{
public:
	UpdatableManager* ptrMgr;
	Updatable* ptrUp;

	CommandUpdateDeregistration() = delete;
	~CommandUpdateDeregistration(){};
	CommandUpdateDeregistration(const CommandUpdateDeregistration&) = delete;
	CommandUpdateDeregistration& operator=(const CommandUpdateDeregistration&) = delete;

	CommandUpdateDeregistration(UpdatableManager* mgr, Updatable* up);
	virtual void execute() override;
};

#endif _CommandUpdateDeregistration