#include "CommandUpdateRegistration.h"

CommandUpdateRegistration::CommandUpdateRegistration(UpdatableManager* mgr, Updatable* up) : ptrMgr(mgr), ptrUp(up)
{

}

void CommandUpdateRegistration::execute()
{
	ptrMgr->Register(ptrUp);
}