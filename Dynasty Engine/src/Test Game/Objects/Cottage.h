#ifndef _Cottage
#define _Cottage

#include "AzulCore.h"
#include "..\..\Dynasty Engine\Game Object\GameObject.h"

class Spaceship;

class Cottage : public GameObject
{
private:
	GraphicsObject_TextureFlat *pGObj_Cottage;

	Vect CottagePos;

	virtual void SceneEntry() override;
	virtual void SceneExit() override;

public:
	Cottage(Vect& startPosition);
	~Cottage();

	float angle;

	virtual void Update() override;
	virtual void Draw() override;
	virtual void Collision(Spaceship*);
	virtual void Collision(Cottage*);
};

#endif _Cottage