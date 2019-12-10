#include "CommandKeyEventDeregistration.h"

CommandKeyEventDeregistration::CommandKeyEventDeregistration(KeyboardEventManager* mgr, Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e) : ptrMgr(mgr), input(in), key(k), kEvent(e)
{

}

void CommandKeyEventDeregistration::execute()
{
	ptrMgr->Deregister(input, key, kEvent);
}