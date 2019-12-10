#include "TimeManager.h"
#include "..\Dynasty.h"

TimeManager* TimeManager::singleInst = NULL;

TimeManager::~TimeManager()
{

}

TimeManager::TimeManager()
{
	//DebugMsg::out("Time Manager Created \n");
	currentTime = 0;
	previousTime = 0;
	frameTime = 0;
}

void TimeManager::pGetTime()
{ 
	Instance().currentTime = Instance().FrzTime.GetTimeInSeconds();
}

void TimeManager::pProcessTime()
{
	Instance().previousTime = Instance().currentTime;

	Instance().currentTime = Instance().FrzTime.GetTimeInSeconds();

	Instance().frameTime = Instance().currentTime - Instance().previousTime;
}

void TimeManager::Delete()
{
	delete singleInst;
	singleInst = NULL;
}

float TimeManager::GetTime()
{
	pGetTime();
	return Instance().currentTime;
}

void TimeManager::ProcessTime()
{
	Instance().pProcessTime();
}