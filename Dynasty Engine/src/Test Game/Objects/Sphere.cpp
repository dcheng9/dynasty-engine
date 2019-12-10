#include "Sphere.h"

#include "..\..\Dynasty Engine\Managers\ModelManager.h"
#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\..\Dynasty Engine\Managers\TextureManager.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"
#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
#include "..\..\Dynasty Engine\Managers\DrawableManager.h"

void Sphere::SceneEntry()
{
	DebugMsg::out("Sphere Entering Scene");

	UpdateRegistration();
	DrawRegistration();
}

void Sphere::SceneExit()
{
	DebugMsg::out("Sphere Exiting Scene");

	UpdateDeregistration();
	DrawDeregistration();
}

Sphere::Sphere()
{
	Vect Yellow(1.0f, 1.0f, 0.0f);
	pGObj_AzulSphere = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingSphere"), ShaderManager::GetShader("shaderConstColor"), Yellow);

	angle = 0.0f;
}

Sphere::~Sphere()
{
	MarkForSceneExit();
}

void Sphere::Update()
{
	Matrix world;
	Matrix Rot;
	Matrix Scale;
	Matrix Trans;

	angle += 0.02f;

	Scale.set(SCALE, 10, 10, 10);
	Rot = Matrix(ROT_Y, angle) * Matrix(ROT_Z, 0.25f*angle);
	Trans.set(TRANS, -40, 30, 0);
	world = Scale * Rot * Trans;
	pGObj_AzulSphere->SetWorld(world);

	static int count = 0;
	if (count == 0)
	{
		pGObj_AzulSphere->pWireColor->set(1.0f, 0.0f, 0.0f);
	}
	else if (count == 100)
	{
		pGObj_AzulSphere->pWireColor->set(0.0f, 1.0f, 0.0f);
	}
	else if (count == 200)
	{
		pGObj_AzulSphere->pWireColor->set(0.0f, 0.0f, 1.0f);
	}
	else if (count > 300)
	{
		count = -1;
	}
	count++;
}

void Sphere::Draw()
{
	pGObj_AzulSphere->Render(GetCamera());
}