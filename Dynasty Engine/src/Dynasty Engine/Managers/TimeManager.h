#ifndef _TimeManager
#define _TimeManager

#include "AzulCore.h"
#include "..\Other Classes\FreezeTime.h"

///
///	\ingroup OtherManagerGroup
///
class TimeManager
{
private:
	~TimeManager();
	static TimeManager* singleInst;

	TimeManager();	// Private constructor
	TimeManager(const TimeManager&) = delete;	// Prevent copy-construction
	TimeManager& operator=(const TimeManager&) = delete;	// Prevent assignment

	static TimeManager& Instance()		// Access reference (all public methods will be static)
	{
		if (!singleInst)
			singleInst = new TimeManager();
		return *singleInst;
	};

	float currentTime;
	float previousTime;
	float frameTime;

	FreezeTime FrzTime;

	static void pGetTime();
	static void pProcessTime();

	friend class Dynasty;
	///
	/// \brief Clears the manager for deletion
	///
	static void Delete();

public:
	///
	/// \brief Returns the current time
	///
	static float GetTime();
	static void ProcessTime();


};
#endif _TimeManager