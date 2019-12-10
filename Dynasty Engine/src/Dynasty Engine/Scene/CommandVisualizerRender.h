#ifndef _CommandVisualizerRender
#define _CommandVisualizerRender

#include "CommandBase.h"
#include "..\Game Object\GameObject.h"

class CollisionVolume;

enum VolumeType;

class CommandVisualizerRender : public CommandBase
{
private:
	CollisionVolume* cVolume;
	const Vect& color;

public:
	CommandVisualizerRender() = delete;
	virtual ~CommandVisualizerRender(){};
	CommandVisualizerRender(const CommandVisualizerRender&) = delete;
	CommandVisualizerRender& operator=(const CommandVisualizerRender&) = delete;

	CommandVisualizerRender(CollisionVolume* cV, const Vect& col);

	virtual void execute() override;
};

#endif _CommandVisualizerRender