#ifndef _BulletFactory
#define _BulletFactory

#include <stack>
#include "AzulCore.h"

class Bullet;
class GameObject;

class BulletFactory
{
private:
	~BulletFactory();

	std::stack<Bullet*> recycledItems;
	static BulletFactory* bulletFactoryInstance;	// Game set up as a singleton (

	BulletFactory() { };		// Private constructor
	BulletFactory(const BulletFactory&){ };	// Prevent copy-construction
	BulletFactory& operator=(const BulletFactory&){ };	// Prevent assignment

	static BulletFactory& Instance()		// Access reference (all public methods will be static)
	{
		if (!bulletFactoryInstance)
			bulletFactoryInstance = new BulletFactory();
		return *bulletFactoryInstance;
	};

	// more private methods, non-static

public:
	// All public methods are static

	static void CreateBullet(const Matrix& rot, const Vect& pos);

	static void RecycleBullet(GameObject* b);  // Arguments must be GameObject since it will be called by the base class
};

#endif _BulletFactory