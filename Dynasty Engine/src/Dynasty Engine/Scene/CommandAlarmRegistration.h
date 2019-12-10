#ifndef _CommandAlarmRegistration
#define _CommandAlarmRegistration

#include "CommandBase.h"
#include "..\Managers\AlarmableManager.h"

class CommandAlarmRegistration : public CommandBase
{
public:
	AlarmableManager* ptrMgr;
	AlarmMarker* ptrAm;

	CommandAlarmRegistration() = delete;
	~CommandAlarmRegistration(){};
	CommandAlarmRegistration(const CommandAlarmRegistration&) = delete;
	CommandAlarmRegistration& operator=(const CommandAlarmRegistration&) = delete;

	CommandAlarmRegistration(AlarmableManager* mgr, AlarmMarker* am);
	virtual void execute() override;
};

#endif _CommandAlarmRegistration