#include "CommandDrawRegistration.h"

CommandDrawRegistration::CommandDrawRegistration(DrawableManager* mgr, Drawable* dr) : ptrMgr(mgr), ptrDr(dr)
{

}

void CommandDrawRegistration::execute()
{
	ptrMgr->Register(ptrDr);
}