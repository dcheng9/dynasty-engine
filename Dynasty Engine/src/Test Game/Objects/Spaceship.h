#ifndef _Spaceship
#define _Spaceship

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"

class Cottage;

class Spaceship : public GameObject
{
private:
	GraphicsObject_TextureFlat *pGObj_SpaceshipWithTexture;
	GraphicsObject_WireframeConstantColor *pGObj_SpaceshipInWireframe;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

	Matrix ShipScale;
	Vect ShipPos;
	Matrix ShipRot;
	Matrix world;

	const float ShipTransSpeed = 1;

	float ShipForwardSpeed;
	float ShipTurnSpeed;

public:
	Spaceship(Vect& startPosition);
	~Spaceship();

	float angle;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void KeyPressed(AZUL_KEY k) override;
	virtual void KeyReleased(AZUL_KEY k) override;
	virtual void Collision(Spaceship*) { DebugMsg::out("Collision Spaceship with Spaceship\n"); }
	virtual void Collision(Cottage*);
	virtual void CollisionTerrain() { DebugMsg::out("Collision Spaceship with Terrain\n"); }
};

#endif _Spaceship