#include "Bullet.h"

#include "..\Other\BulletFactory.h"

#include "..\..\Dynasty Engine\Managers\ModelManager.h"
#include "..\..\Dynasty Engine\Managers\ShaderManager.h"
#include "..\..\Dynasty Engine\Managers\TextureManager.h"
#include "..\..\Dynasty Engine\Managers\CameraManager.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"
#include "..\..\Dynasty Engine\Managers\UpdatableManager.h"
#include "..\..\Dynasty Engine\Managers\DrawableManager.h"

void Bullet::SceneEntry()
{
	AlarmRegistration(AlarmID_0, lifetime);
	UpdateRegistration();
	DrawRegistration();
}

void Bullet::SceneExit()
{
	DebugMsg::out("Bullet Exiting Scene \n");

	AlarmDeregistration(AlarmID_0);
	UpdateDeregistration();
	DrawDeregistration();

	BulletFactory::RecycleBullet(this);
}

Bullet::Bullet()
{
	Vect Yellow(1.0f, 1.0f, 0.0f);
	pGObj_Bullet = new GraphicsObject_WireframeConstantColor(ModelManager::GetModel("modelBoundingSphere"), ShaderManager::GetShader("shaderConstColor"), Yellow);

	angle = 0.0f;

	BulletScale.set(SCALE, 0.5f, 0.5f, 0.5f);
	world = BulletScale * BulletRot * Matrix(TRANS, BulletPos);
	pGObj_Bullet->SetWorld(world);
}

void Bullet::Initialize(const Matrix& rot, const Vect& pos)
{
	BulletRot = rot;
	BulletPos = pos;
}

Bullet::~Bullet()
{
	//UpdateDeregistration();
	//DrawDeregistration();

	BulletFactory::RecycleBullet(this);
}

void Bullet::Update()
{
	BulletPos += Vect(0, 0, 1) * BulletRot * BulletTransSpeed;

	world = BulletScale * BulletRot * Matrix(TRANS, BulletPos);
	pGObj_Bullet->SetWorld(world);
}

void Bullet::Draw()
{
	pGObj_Bullet->Render(GetSceneCamera());
}

void Bullet::Alarm0()
{
	MarkForSceneExit();
}