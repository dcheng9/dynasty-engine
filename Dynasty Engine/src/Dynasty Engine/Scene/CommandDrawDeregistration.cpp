#include "CommandDrawDeregistration.h"

CommandDrawDeregistration::CommandDrawDeregistration(DrawableManager* mgr, Drawable* dr) : ptrMgr(mgr), ptrDr(dr)
{

}

void CommandDrawDeregistration::execute()
{
	ptrMgr->Deregister(ptrDr);
}