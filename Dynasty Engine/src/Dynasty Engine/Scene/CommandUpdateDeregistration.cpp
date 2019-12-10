#include "CommandUpdateDeregistration.h"

CommandUpdateDeregistration::CommandUpdateDeregistration(UpdatableManager* mgr, Updatable* up) : ptrMgr(mgr), ptrUp(up)
{

}

void CommandUpdateDeregistration::execute()
{
	ptrMgr->Deregister(ptrUp);
}