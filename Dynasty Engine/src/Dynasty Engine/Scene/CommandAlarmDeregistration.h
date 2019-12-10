#ifndef _CommandAlarmDeregistration
#define _CommandAlarmDeregistration

#include "CommandBase.h"
#include "..\Managers\AlarmableManager.h"

class CommandAlarmDeregistration : public CommandBase
{
public:
	AlarmableManager* ptrMgr;
	AlarmMarker* ptrAm;

	CommandAlarmDeregistration() = delete;
	~CommandAlarmDeregistration(){};
	CommandAlarmDeregistration(const CommandAlarmDeregistration&) = delete;
	CommandAlarmDeregistration& operator=(const CommandAlarmDeregistration&) = delete;

	CommandAlarmDeregistration(AlarmableManager* mgr, AlarmMarker* am);
	virtual void execute() override;
};

#endif _CommandAlarmDeregistration