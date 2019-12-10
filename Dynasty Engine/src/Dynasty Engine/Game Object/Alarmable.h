#ifndef _Alarmable
#define _Alarmable

#include "AzulCore.h"

class AlarmMarker;
class Scene;

enum AlarmID { AlarmID_0 = 0, AlarmID_1 = 1, AlarmID_2 = 2 };

///
///	\ingroup GameObjectGroup
///
class Alarmable
{
private:
	const static int MAX_ALARMS = 3;
	AlarmMarker* ptrAm[MAX_ALARMS];

	virtual Scene* GetGOScene() = 0;

public:
	Alarmable();
	~Alarmable();
	Alarmable(const Alarmable&) = delete;
	Alarmable& operator=(const Alarmable&) = delete;

	///
	///	\ingroup GameObjectGroup
	///	
	/// \brief Use this function to program what you want to happen when AlarmID_0 goes off
	///
	virtual void Alarm0(){};
	///
	/// \brief Use this function to program what you want to happen when AlarmID_1 goes off
	///
	virtual void Alarm1(){};
	///
	/// \brief Use this function to program what you want to happen when AlarmID_2 goes off
	///
	virtual void Alarm2(){};

	///
	/// \brief Called when you want to register an Alarm in a GameObject
	///		\param id The alarm number, from 0-2, EX: AlarmID_1
	///		\param t How long you want the alarm to go for until it goes off
	///
	void Alarmable::AlarmRegistration(AlarmID id, float t);
	///
	/// \brief Called when you want to deregister an Alarm in a GameObject
	///		\param id The alarm number, from 0-2, EX: AlarmID_1
	///
	void Alarmable::AlarmDeregistration(AlarmID id);
	///
	/// \brief Internally calls the correct Alarm based on the id passed in
	///
	/// \param id The Alarm function that will be called
	///
	void Alarmable::Dispatch(AlarmID id);
};

#endif _Alarmable