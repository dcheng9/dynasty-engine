#include "Drawable.h"
#include "..\Managers\SceneManager.h"
#include "..\Scene\Scene.h"

void Drawable::DrawRegistration()
{
	GetGOScene()->RegisterDraw(this);
}

void Drawable::DrawDeregistration()
{
	GetGOScene()->DeregisterDraw(this);
}