#ifndef _AlarmMarker
#define _AlarmMarker

#include "AzulCore.h"
#include "Alarmable.h"

///
///	\ingroup OtherInternalGroup
///
class AlarmMarker
{
private:
	Alarmable* ptrAl;
	AlarmID markID;

	float triggerTime;

public:
	AlarmMarker(){};
	AlarmMarker(Alarmable* ptr, AlarmID id, float t);
	virtual ~AlarmMarker(){};
	AlarmMarker(const AlarmMarker&) = delete;
	AlarmMarker& operator=(const AlarmMarker&) = delete;

	///
	/// \brief Calls the linked Alarmable's Dispatch
	///
	void CallEvent();
	///
	/// \brief Returns the triggerTime
	///
	float GetTriggerTime();
};

#endif _AlarmMarker