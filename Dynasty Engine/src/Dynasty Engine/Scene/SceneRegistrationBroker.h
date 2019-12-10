#ifndef _SceneRegistrationBroker
#define _SceneRegistrationBroker

#include <list>
#include "AzulCore.h"
#include "CommandBase.h"

///
///	\ingroup OtherInternalGroup
///
class SceneRegistrationBroker
{
public:
	std::list<CommandBase*> commandList;

	SceneRegistrationBroker(){};
	~SceneRegistrationBroker();
	SceneRegistrationBroker(const SceneRegistrationBroker&) = delete;
	SceneRegistrationBroker& operator=(const SceneRegistrationBroker&) = delete;

	///
	/// \brief Adds a command to the list
	///
	void addCommand(CommandBase* cmd);
	///
	/// \brief Iterate through the list and call execute on each command
	///
	void ExecuteCommands();
};

#endif _SceneRegistrationBroker