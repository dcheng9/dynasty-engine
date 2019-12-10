#include "SceneRegistrationBroker.h"

SceneRegistrationBroker::~SceneRegistrationBroker()
{
	for (std::list<CommandBase*>::iterator it = commandList.begin(); it != commandList.end(); it++)
	{
		if (*it != NULL)
			delete (*it);
	}
	commandList.clear();
}

void SceneRegistrationBroker::addCommand(CommandBase* cmd)
{
	commandList.push_back(cmd);
}

void SceneRegistrationBroker::ExecuteCommands()
{
	for (std::list<CommandBase*>::iterator it = commandList.begin(); it != commandList.end(); it++)
	{
		(*it)->execute();
		delete (*it);
	}
	commandList.clear();
}