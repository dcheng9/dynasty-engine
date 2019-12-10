#ifndef _Sphere
#define _Sphere

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"

class Sphere : public GameObject
{
private:
	GraphicsObject_WireframeConstantColor *pGObj_AzulSphere;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

public:
	Sphere();
	~Sphere();

	float angle;

	virtual void Update() override;
	virtual void Draw() override;
};

#endif _Sphere