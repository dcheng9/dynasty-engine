#ifndef _Box
#define _Box

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"

class Box : public GameObject
{
private:
	GraphicsObject_WireframeConstantColor *pGObj_AzulBox;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

public:
	Box();
	~Box();

	float angle;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void KeyPressed(AZUL_KEY k) override;
};

#endif _Box