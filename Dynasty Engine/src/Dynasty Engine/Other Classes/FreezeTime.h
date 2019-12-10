// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

///
///	\ingroup OtherInternalGroup
///
class FreezeTime
{
private:
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F10;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F11;

	float totalFrozenTime;
	bool freeze_mode_active;

	float WaitAndReturnFrozenTime(float activetime);
	bool HackedKeyRelease(AZUL_KEY k);

public:
	FreezeTime();
	~FreezeTime(){};
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

	float GetTimeInSeconds();
};

#endif _FreezeTime