#ifndef _Bullet
#define _Bullet

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"


class Bullet : public GameObject
{
private:
	GraphicsObject_WireframeConstantColor *pGObj_Bullet;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

	Matrix BulletScale;
	Vect BulletPos;
	Matrix BulletRot;
	Matrix world;

	const float BulletTransSpeed = 1;
	const float lifetime = 2.0f;

public:
	Bullet();
	~Bullet();

	void Initialize(const Matrix& rot, const Vect& pos);

	float angle;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Alarm0() override;
};

#endif _Bullet