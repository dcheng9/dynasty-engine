#ifndef _SceneTest
#define _SceneTest

#include "..\..\Dynasty Engine\Scene\Scene.h"

class Spaceship;
class Box;
class Cottage;
class GodCamera;

class SceneTest : public Scene
{
public:
	SceneTest(){};
	virtual ~SceneTest(){};
	SceneTest(const SceneTest&) = delete;
	SceneTest& operator=(const SceneTest&) = delete;

private:

	virtual void Initialize() override;
	virtual void SceneEnd() override;

	Spaceship* testSpaceship;
	Spaceship* testSpaceship2;
	Spaceship* testSpaceship3;
	Box* testBox;
	Cottage* testCottage1;
	Cottage* testCottage2;
	Cottage* testCottage3;
	Cottage* testCottage4;
	GodCamera* godCam;
};

#endif _SceneTest