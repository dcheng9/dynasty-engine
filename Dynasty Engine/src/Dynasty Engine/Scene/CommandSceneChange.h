#ifndef _CommandSceneChange
#define _CommandSceneChange

#include "CommandBase.h"

class Scene;

class CommandSceneChange : public CommandBase
{
public:
	Scene* ptrSc;

	CommandSceneChange() = delete;
	~CommandSceneChange(){};
	CommandSceneChange(const CommandSceneChange&) = delete;
	CommandSceneChange& operator=(const CommandSceneChange&) = delete;

	CommandSceneChange(Scene* nextScene);
	///
	/// \brief Call to end the current Scene, delete it, and change to the next Scene
	///
	virtual void execute() override;
};

#endif _CommandSceneChange