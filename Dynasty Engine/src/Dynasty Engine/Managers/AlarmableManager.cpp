#include "AlarmableManager.h"
#include "TimeManager.h"
#include "..\Dynasty.h"

#include <string>
#include "..\Game Object\AlarmMarker.h"


AlarmableManager::~AlarmableManager()
{
	tlMap.clear();
}

void AlarmableManager::ProcessElements()
{
	TimelineMap::iterator it = tlMap.begin();
	while (it != tlMap.end() && TimeManager::GetTime() >= it->first)
	{
		it->second->CallEvent();
		tlMap.erase(it);
		it = tlMap.begin();
	}
}

void AlarmableManager::Register(AlarmMarker* am)
{
	tlMap[Dynasty::GetTime() + am->GetTriggerTime()] = am;
}

void AlarmableManager::Deregister(AlarmMarker* am)
{
	for (TimelineMap::iterator it = tlMap.begin(); it != tlMap.end();)
	{
		if (it->second == am)
			tlMap.erase(it++);
		else
			it++;
	}
}

void AlarmableManager::Delete()
{
	TimelineMap::iterator it = tlMap.begin();
	while (it != tlMap.end())
	{
		it->second->CallEvent();
		tlMap.erase(it);
		it = tlMap.begin();
	}

	tlMap.clear();
}