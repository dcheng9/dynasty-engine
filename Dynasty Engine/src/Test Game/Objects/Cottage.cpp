#include "Cottage.h"

#include "..\..\Dynasty Engine\Managers\ModelManager.h"
#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\..\Dynasty Engine\Managers\TextureManager.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"
#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
#include "..\..\Dynasty Engine\Managers\DrawableManager.h"
#include "..\..\Dynasty Engine\Collider\Visualizer.h"

#include "..\..\Dynasty Engine\Collider\BoundingSphere.h"
#include "..\..\Dynasty Engine\Collider\AABB.h"

void Cottage::SceneEntry()
{
	DebugMsg::out("Cottage Entering Scene \n");

	UpdateRegistration();
	DrawRegistration();

	CollisionRegistration<Cottage>(this);

	Visualizer::Register(cVolume, Vect(0.0f, 0.0f, 0.0f, 0.0f));
	Visualizer::Register(GetBSphere(), Vect(0.0f, 0.0f, 0.0f, 0.0f));
}

void Cottage::SceneExit()
{
	DebugMsg::out("Cottage Exiting Scene \n");

	UpdateDeregistration();
	DrawDeregistration();

	CollisionDeregistration<Cottage>(this);
}

Cottage::Cottage(Vect& startPosition)
{
	pGObj_Cottage = new GraphicsObject_TextureFlat(ModelManager::GetModel("modelCottage"), ShaderManager::GetShader("shaderFlat"), TextureManager::GetTexture("textCottage0"), TextureManager::GetTexture("textCottage1"), TextureManager::GetTexture("textCottage2"), TextureManager::GetTexture("textCottage3"));

	angle = 0.0f;

	CottagePos.set(startPosition);

	SetColliderModel(pGObj_Cottage->getModel(), OBBtype);
	UpdateCollisionData(pGObj_Cottage->getWorld());
}

Cottage::~Cottage()
{
	DebugMsg::out("Cottage Exiting Scene \n");

	//UpdateDeregistration();
	//DrawDeregistration();

	//CollisionDeregistration<Cottage>(this);
}

void Cottage::Update()
{
	Matrix world;
	Matrix Rot;
	Matrix Scale;

	angle += 0.02f;

	Scale.set(SCALE, 2, 2, 2);
	Rot.set(ROT_Y, angle);
	world = Scale * Rot * Matrix(TRANS, CottagePos);
	pGObj_Cottage->SetWorld(world);

	UpdateCollisionData(pGObj_Cottage->getWorld());
}

void Cottage::Draw()
{
	pGObj_Cottage->Render(GetSceneCamera());
}

void Cottage::Collision(Spaceship*)
{
	DebugMsg::out("Collision Cottage with Spaceship\n");
}

void Cottage::Collision(Cottage*)
{
}