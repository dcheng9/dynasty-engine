#ifndef _CommandKeyEventDeregistration
#define _CommandKeyEventDeregistration

#include "CommandBase.h"
#include "..\Managers\KeyboardEventManager.h"

class CommandKeyEventDeregistration : public CommandBase
{
public:
	KeyboardEventManager* ptrMgr;
	Inputable* input;
	AZUL_KEY key;
	INPUT_EVENT_TYPE kEvent;

	CommandKeyEventDeregistration() = delete;
	~CommandKeyEventDeregistration(){};
	CommandKeyEventDeregistration(const CommandKeyEventDeregistration&) = delete;
	CommandKeyEventDeregistration& operator=(const CommandKeyEventDeregistration&) = delete;

	CommandKeyEventDeregistration(KeyboardEventManager* mgr, Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e);
	virtual void execute() override;
};

#endif _CommandKeyEventDeregistration