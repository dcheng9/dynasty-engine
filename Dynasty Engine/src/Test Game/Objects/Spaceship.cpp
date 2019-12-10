#include "Spaceship.h"

#include "..\Other\BulletFactory.h"

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
#include "..\..\Dynasty Engine\Collider\OBB.h"

void Spaceship::SceneEntry()
{
	DebugMsg::out("Spaceship Entering Scene \n");

	UpdateRegistration();
	DrawRegistration();
	KeyEventRegistration(KEY_W, KEY_PRESS);
	KeyEventRegistration(KEY_A, KEY_PRESS);
	KeyEventRegistration(KEY_S, KEY_PRESS);
	KeyEventRegistration(KEY_D, KEY_PRESS);
	KeyEventRegistration(KEY_SPACE, KEY_PRESS);
	KeyEventRegistration(KEY_W, KEY_RELEASE);
	KeyEventRegistration(KEY_A, KEY_RELEASE);
	KeyEventRegistration(KEY_S, KEY_RELEASE);
	KeyEventRegistration(KEY_D, KEY_RELEASE);

	CollisionRegistration<Spaceship>(this);

	Visualizer::Register(cVolume, Vect(0.0f, 0.0f, 0.0f, 0.0f));
	Visualizer::Register(GetBSphere(), Vect(0.0f, 0.0f, 0.0f, 0.0f));
}

void Spaceship::SceneExit()
{
	DebugMsg::out("Spaceship Exiting Scene \n");

	UpdateDeregistration();
	DrawDeregistration();
	KeyEventDeregistration(KEY_W, KEY_PRESS);
	KeyEventDeregistration(KEY_A, KEY_PRESS);
	KeyEventDeregistration(KEY_S, KEY_PRESS);
	KeyEventDeregistration(KEY_D, KEY_PRESS);
	KeyEventDeregistration(KEY_SPACE, KEY_PRESS);
	KeyEventDeregistration(KEY_W, KEY_RELEASE);
	KeyEventDeregistration(KEY_A, KEY_RELEASE);
	KeyEventDeregistration(KEY_S, KEY_RELEASE);
	KeyEventDeregistration(KEY_D, KEY_RELEASE);

	CollisionDeregistration<Spaceship>(this);
}

Spaceship::Spaceship(Vect& startPosition)
{
	pGObj_SpaceshipWithTexture = new GraphicsObject_TextureFlat(ModelManager::GetModel("modelSpaceFrigate"), ShaderManager::GetShader("shaderFlat"), TextureManager::GetTexture("textSpaceFrigate"));
	
	angle = 0.0f;
	ShipForwardSpeed = 0.0f;
	ShipTurnSpeed = 0.0f;

	ShipScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	ShipRot.set(IDENTITY);
	ShipPos.set(startPosition);
	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceshipWithTexture->SetWorld(world);

	SetColliderModel(pGObj_SpaceshipWithTexture->getModel(), AABBtype);
	UpdateCollisionData(pGObj_SpaceshipWithTexture->getWorld());
}

Spaceship::~Spaceship()
{
	//UpdateDeregistration();
	//DrawDeregistration();
	//KeyEventDeregistration(KEY_W, KEY_PRESS);
	//KeyEventDeregistration(KEY_A, KEY_PRESS);
	//KeyEventDeregistration(KEY_S, KEY_PRESS);
	//KeyEventDeregistration(KEY_D, KEY_PRESS);
	//KeyEventDeregistration(KEY_SPACE, KEY_PRESS);
	//KeyEventDeregistration(KEY_W, KEY_RELEASE);
	//KeyEventDeregistration(KEY_A, KEY_RELEASE);
	//KeyEventDeregistration(KEY_S, KEY_RELEASE);
	//KeyEventDeregistration(KEY_D, KEY_RELEASE);

	//CollisionDeregistration<Spaceship>(this);

	DebugMsg::out("Spaceship Exiting Scene \n");
}

void Spaceship::Update()
{
	ShipPos += Vect(0, 0, 1) * ShipRot * ShipTransSpeed * ShipForwardSpeed;
	ShipRot *= Matrix(ROT_Y, ShipTurnSpeed);

	world = ShipScale * ShipRot * Matrix(TRANS, ShipPos);
	pGObj_SpaceshipWithTexture->SetWorld(world);

	UpdateCollisionData(world);
}

void Spaceship::Draw()
{
	pGObj_SpaceshipWithTexture->Render(GetSceneCamera());
	Visualizer::HighlightTerrain(GetBSphere());
}

void Spaceship::KeyPressed(AZUL_KEY k)
{
	if (k == KEY_W)
	{
		ShipForwardSpeed = 1;
	}
	else if (k == KEY_S)
	{
		ShipForwardSpeed = -1;
	}
	else if (k == KEY_A)
	{
		ShipTurnSpeed = .05f;
	}
	else if (k == KEY_D)
	{
		ShipTurnSpeed = -.05f;
	}
	else if (k == KEY_SPACE)
	{
		BulletFactory::CreateBullet(ShipRot, ShipPos);
	}
}

void Spaceship::KeyReleased(AZUL_KEY k)
{
	if (k == KEY_W || k == KEY_S)
	{
		ShipForwardSpeed = 0;
	}
	else if (k == KEY_A || k == KEY_D)
	{
		ShipTurnSpeed = 0;
	}
}

void Spaceship::Collision(Cottage*)
{
	DebugMsg::out("Collision Spaceship with Cottage\n"); 
}