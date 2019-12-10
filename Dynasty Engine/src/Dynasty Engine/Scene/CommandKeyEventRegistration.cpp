#include "CommandKeyEventRegistration.h"

CommandKeyEventRegistration::CommandKeyEventRegistration(KeyboardEventManager* mgr, Inputable* in, AZUL_KEY k, INPUT_EVENT_TYPE e) : ptrMgr(mgr), input(in), key(k), kEvent(e)
{

}

void CommandKeyEventRegistration::execute()
{
	ptrMgr->Register(input, key, kEvent);
}