#include "..\Dynasty Engine\Dynasty.h"

void Dynasty::GameInitialize()
{
	DebugMsg::out("Game() started\n");

	// Game Window Device setup
	Dynasty::SetWindowName("Dynasty Engine Test");
	Dynasty::SetWidthHeight(800, 600);
	Dynasty::SetClear(0.4f, 0.4f, 0.8f, 1.0f);
}