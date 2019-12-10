#include "CommandVisualizerRender.h"
#include "..\Collider\Visualizer.h"
#include "..\Collider\CollisionVolume.h"

CommandVisualizerRender::CommandVisualizerRender(CollisionVolume* cv, const Vect& col) : cVolume(cv), color(col)
{

}

void CommandVisualizerRender::execute()
{
	switch (cVolume->vType)
	{
	case BStype:
		Visualizer::RenderBS(cVolume, color);
		break;
	case AABBtype:
		Visualizer::RenderAABBOBB(cVolume, color);
		break;
	case OBBtype:
		Visualizer::RenderAABBOBB(cVolume, color);
		break;
	default:
		break;
	}
}