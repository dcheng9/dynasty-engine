#ifndef _IntroScene
#define _IntroScene

#include "..\..\Dynasty Engine\Scene\Scene.h"

class Box;
class GodCamera;

class IntroScene : public Scene
{
public:
	IntroScene(){};
	virtual ~IntroScene(){};
	IntroScene(const IntroScene&) = delete;
	IntroScene& operator=(const IntroScene&) = delete;

private:

	virtual void Initialize() override;
	virtual void SceneEnd() override;

	Box* testBox;
	GodCamera* godCam;
};

#endif _IntroScene