#ifndef _CommandSceneAddObject
#define _CommandSceneAddObject

#include "CommandBase.h"
#include "..\Game Object\GameObject.h"

class CommandSceneAddObject : public CommandBase
{
public:
	GameObject* ptrGO;
	Scene* ptrSc;

	CommandSceneAddObject() = delete;
	~CommandSceneAddObject(){};
	CommandSceneAddObject(const CommandSceneAddObject&) = delete;
	CommandSceneAddObject& operator=(const CommandSceneAddObject&) = delete;

	CommandSceneAddObject(Scene* sc, GameObject* go);
	///
	/// \brief Gives the new GameObject the current Scene and calls its SceneEntry
	///
	virtual void execute() override;
};

#endif _CommandSceneAddObject