#include "Alarmable.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\Scene.h"
#include "..\Game Object\AlarmMarker.h"

Alarmable::Alarmable()
{
	for (int i = 0; i < MAX_ALARMS; i++)
	{
		ptrAm[i] = NULL;
	}
}

Alarmable::~Alarmable()
{
	for(int i = 0; i < MAX_ALARMS; i++)
	{
		if (ptrAm[i] != NULL)
		{
			delete ptrAm[i];
		}
	}
}

void Alarmable::AlarmRegistration(AlarmID id, float t)
{
	if (ptrAm[id] != NULL)
	{
		delete ptrAm[id];
		ptrAm[id] = NULL;
	}
	ptrAm[id] = new AlarmMarker(this, id, t);
	GetGOScene()->RegisterAlarm(ptrAm[id]);
	DebugMsg::out("Alarm Set\n");
}

void Alarmable::AlarmDeregistration(AlarmID id)
{
	GetGOScene()->DeregisterAlarm(ptrAm[id]);
	if (ptrAm[id] != NULL)
	{
		delete ptrAm[id];
		ptrAm[id] = NULL;
	}
	DebugMsg::out("Alarm Deregistered\n");
}

void Alarmable::Dispatch(AlarmID id)
{
	switch (id)
	{
	case AlarmID_0:
		Alarm0();
		break;
	case AlarmID_1:
		Alarm1();
		break;
	case AlarmID_2:
		Alarm2();
		break;
	default:
		break;
	}
}