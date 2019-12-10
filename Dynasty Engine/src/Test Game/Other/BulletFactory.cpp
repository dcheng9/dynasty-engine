#include "BulletFactory.h"
#include "..\Objects\Bullet.h"
#include "..\..\Dynasty Engine\Managers\SceneManager.h"

BulletFactory* BulletFactory::bulletFactoryInstance = NULL;

void BulletFactory::CreateBullet(const Matrix& rot, const Vect& pos)
{
	Bullet* b;

	if (Instance().recycledItems.empty())
	{
		b = new Bullet();
		DebugMsg::out("Bullet Created \n");
	}
	else
	{
		b = Instance().recycledItems.top();
		Instance().recycledItems.pop();
		DebugMsg::out("Bullet Recycled \n");
	}

	b->Initialize(rot, pos);
	SceneManager::AddToScene(b);
}

void BulletFactory::RecycleBullet(GameObject* b)
{
	Instance().recycledItems.push((Bullet*)b);
}

BulletFactory::~BulletFactory()
{
	// forcefully delele all recycled gameobjects
	while (!Instance().recycledItems.empty())
	{
		delete Instance().recycledItems.top();
		Instance().recycledItems.pop();
	}

	delete bulletFactoryInstance;
	bulletFactoryInstance = NULL;
}