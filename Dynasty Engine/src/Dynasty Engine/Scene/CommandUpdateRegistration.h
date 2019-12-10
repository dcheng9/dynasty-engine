#ifndef _CommandUpdateRegistration
#define _CommandUpdateRegistration

#include "CommandBase.h"
#include "..\Managers\UpdatableManager.h"

class CommandUpdateRegistration : public CommandBase
{
public:
	UpdatableManager* ptrMgr;
	Updatable* ptrUp;

	CommandUpdateRegistration() = delete;
	~CommandUpdateRegistration(){};
	CommandUpdateRegistration(const CommandUpdateRegistration&) = delete;
	CommandUpdateRegistration& operator=(const CommandUpdateRegistration&) = delete;

	CommandUpdateRegistration(UpdatableManager* mgr, Updatable* up);
	virtual void execute() override;
};

#endif _CommandUpdateRegistration