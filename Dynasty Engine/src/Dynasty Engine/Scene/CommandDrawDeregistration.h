#ifndef _CommandDrawDeregistration
#define _CommandDrawDeregistration

#include "CommandBase.h"
#include "..\Managers\DrawableManager.h"

class CommandDrawDeregistration : public CommandBase
{
public:
	DrawableManager* ptrMgr;
	Drawable* ptrDr;

	CommandDrawDeregistration() = delete;
	~CommandDrawDeregistration(){};
	CommandDrawDeregistration(const CommandDrawDeregistration&) = delete;
	CommandDrawDeregistration& operator=(const CommandDrawDeregistration&) = delete;

	CommandDrawDeregistration(DrawableManager* mgr, Drawable* dr);
	virtual void execute() override;
};

#endif _CommandDrawDeregistration