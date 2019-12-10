#include "Box.h"

#include "..\..\Dynasty Engine\Managers\ModelManager.h"
#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\..\Dynasty Engine\Managers\TextureManager.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"
#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
#include "..\..\Dynasty Engine\Managers\DrawableManager.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"

#include "..\Scenes\SceneTest.h"

void Box::SceneEntry()
{
	DebugMsg::out("Box Entering Scene \n");

	UpdateRegistration();
	DrawRegistration();
	KeyEventRegistration(KEY_E, KEY_PRESS);
}

void Box::SceneExit()
{
	DebugMsg::out("Box Exiting Scene \n");

	UpdateDeregistration();
	DrawDeregistration();
	KeyEventDeregistration(KEY_E, KEY_PRESS);
}

Box::Box()
{
	Vect Yellow(1.0f, 1.0f, 0.0f);
	pGObj_AzulBox = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingBox"), ShaderManager::GetShader("shaderConstColor"), Yellow);

	angle = 0.0f;
}

Box::~Box()
{
	//UpdateDeregistration();
	//DrawDeregistration();
	//KeyEventDeregistration(KEY_E, KEY_PRESS);

	DebugMsg::out("Box Exiting Scene \n");
}

void Box::Update()
{
	Matrix world;
	Matrix Rot;
	Matrix Scale;
	Matrix Trans;

	angle += 0.02f;

	Scale.set(SCALE, 10, 10, 10);
	Rot = Matrix(ROT_Y, angle) * Matrix(ROT_Z, 0.25f*angle);
	Trans.set(TRANS, 40, 30, 0);
	world = Scale * Rot * Trans;
	pGObj_AzulBox->SetWorld(world);
}

void Box::Draw()
{
	pGObj_AzulBox->Render(GetSceneCamera());
}

void Box::KeyPressed(AZUL_KEY k)
{
	if (k == KEY_E)
	{
		DebugMsg::out("Changing Scene \n");
		SceneManager::SetNextScene(new SceneTest);
	}
}