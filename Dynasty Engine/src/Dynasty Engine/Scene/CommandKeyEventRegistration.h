#ifndef _CommandKeyEventRegistration
#define _CommandDrawRegistration

#include "CommandBase.h"
#include "..\Managers\KeyboardEventManager.h"

class CommandKeyEventRegistration : public CommandBase
{
public:
	KeyboardEventManager* ptrMgr;
	Inputable* input;
	AZUL_KEY key;
	INPUT_EVENT_TYPE kEvent;

	CommandKeyEventRegistration() = delete;
	~CommandKeyEventRegistration(){};
	CommandKeyEventRegistration(const CommandKeyEventRegistration&) = delete;
	CommandKeyEventRegistration& operator=(const CommandKeyEventRegistration&) = delete;

	CommandKeyEventRegistration(KeyboardEventManager* mgr, Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);
	virtual void execute() override;
};

#endif _CommandKeyEventRegistration