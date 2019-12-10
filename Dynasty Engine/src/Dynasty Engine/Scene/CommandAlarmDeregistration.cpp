#include "CommandAlarmDeregistration.h"

CommandAlarmDeregistration::CommandAlarmDeregistration(AlarmableManager* mgr, AlarmMarker* am) : ptrMgr(mgr), ptrAm(am)
{

}

void CommandAlarmDeregistration::execute()
{
	ptrMgr->Deregister(ptrAm);
}