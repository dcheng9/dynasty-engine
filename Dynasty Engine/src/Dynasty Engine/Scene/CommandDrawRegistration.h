#ifndef _CommandDrawRegistration
#define _CommandDrawRegistration

#include "CommandBase.h"
#include "..\Managers\DrawableManager.h"

class CommandDrawRegistration : public CommandBase
{
public:
	DrawableManager* ptrMgr;
	Drawable* ptrDr;

	CommandDrawRegistration() = delete;
	~CommandDrawRegistration(){};
	CommandDrawRegistration(const CommandDrawRegistration&) = delete;
	CommandDrawRegistration& operator=(const CommandDrawRegistration&) = delete;

	CommandDrawRegistration(DrawableManager* mgr, Drawable* dr);
	virtual void execute() override;
};

#endif _CommandDrawRegistration