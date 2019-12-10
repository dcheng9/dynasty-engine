#include "CommandAlarmRegistration.h"

CommandAlarmRegistration::CommandAlarmRegistration(AlarmableManager* mgr, AlarmMarker* am) : ptrMgr(mgr), ptrAm(am)
{

}

void CommandAlarmRegistration::execute()
{
	ptrMgr->Register(ptrAm);
}