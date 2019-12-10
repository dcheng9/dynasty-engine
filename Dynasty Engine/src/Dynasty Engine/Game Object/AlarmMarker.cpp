#include "AlarmMarker.h"

AlarmMarker::AlarmMarker(Alarmable* ptr, AlarmID id, float t)
{
	ptrAl = ptr;
	markID = id;
	triggerTime = t;
}

void AlarmMarker::CallEvent()
{
	ptrAl->Dispatch(markID);
}

float AlarmMarker::GetTriggerTime()
{
	return triggerTime;
}