#ifndef _CommandSceneRemoveObject
#define _CommandSceneRemoveObject

#include "CommandBase.h"
#include "..\Game Object\GameObject.h"

class CommandSceneRemoveObject : public CommandBase
{
public:
	GameObject* ptrGO;

	CommandSceneRemoveObject() = delete;
	~CommandSceneRemoveObject(){};
	CommandSceneRemoveObject(const CommandSceneRemoveObject&) = delete;
	CommandSceneRemoveObject& operator=(const CommandSceneRemoveObject&) = delete;

	CommandSceneRemoveObject(GameObject* go);
	virtual void execute() override;
};

#endif _CommandSceneRemoveObject